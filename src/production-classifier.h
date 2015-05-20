// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_PRODUCTION_CLASSIFIER_H
#define V8_PRODUCTION_CLASSIFIER_H

#include "src/v8.h"

#include "src/messages.h"
#include "src/zone-containers.h"

namespace v8 {
namespace internal {


class ProductionClassifier {
 public:
  explicit ProductionClassifier(Zone* zone)
      : buffer_(0, zone) {
    buffer_.reserve(128);
  }
  
  enum TargetProduction {
    ExpressionProduction = 1 << 0,
    BindingPatternProduction = 1 << 1,
    AssignmentPatternProduction = 1 << 2,
    DistinctFormalParametersProduction = 1 << 3,
    StrictModeFormalParametersProduction = 1 << 4,
    StrongModeFormalParametersProduction = 1 << 5,
    ArrowFormalParametersProduction = 1 << 6,
  };

  static const unsigned PatternProductions =
      BindingPatternProduction | AssignmentPatternProduction;
  static const unsigned FormalParametersProductions =
      DistinctFormalParametersProduction |
      StrictModeFormalParametersProduction |
      StrongModeFormalParametersProduction;
  static const unsigned StandardProductions =
      ExpressionProduction | PatternProductions;
  static const unsigned AllProductions =
      StandardProductions | FormalParametersProductions |
      ArrowFormalParametersProduction;

  class Error {
   public:
    Error(const Scanner::Location& location, MessageTemplate::Template message,
          const char* arg)
        : location_(location), message_(message), arg_(arg) {}

    const Scanner::Location& location() const { return location_; }
    MessageTemplate::Template message() const { return message_; }
    const char* arg() const { return arg_; }

   private:
    Scanner::Location location_;
    MessageTemplate::Template message_;
    const char* arg_;
  };

  class BufferElement {
   public:
    enum Kind { Leaf, Skip };

    BufferElement() {}  // Needed for std::vector implementation.

    BufferElement(TargetProduction invalid_productions,
                  const Scanner::Location& loc,
                  MessageTemplate::Template message, const char* arg)
        : kind_(Leaf),
          invalid_productions_(invalid_productions),
          error_(loc, message, arg) {}

    BufferElement(unsigned invalid_productions, size_t skip)
        : kind_(Skip),
          invalid_productions_(invalid_productions),
          skip_(skip) {}

    bool is_leaf() const { return kind_ == Leaf; }
    bool is_skip() const { return kind_ == Skip; }

    const Error& error() const {
      DCHECK(is_leaf());
      return error_;
    }

    unsigned invalid_productions() const { return invalid_productions_; }

    size_t skip() const {
      return is_leaf() ? 0 : skip_;
    }

   private:
    Kind kind_;
    unsigned invalid_productions_;
    union {
      size_t skip_;
      Error error_;
    };
  };

  class Cursor {
   public:
    explicit Cursor(ProductionClassifier* classifier)
        : classifier_(classifier),
          start_(classifier->buffer_.size()),
          invalid_productions_(0) {}
    ~Cursor() {
      classifier_->pop(*this);
    }
    unsigned invalid_productions() const { return invalid_productions_; }
    size_t start() const { return start_; }

    bool is_valid_expression() const { return is_valid(ExpressionProduction); }

    bool is_valid_binding_pattern() const {
      return is_valid(BindingPatternProduction);
    }

    bool is_valid_assignment_pattern() const {
      return is_valid(AssignmentPatternProduction);
    }

    bool is_valid_arrow_formal_parameters() const {
      return is_valid(ArrowFormalParametersProduction);
    }

    bool is_valid_formal_parameter_list_without_duplicates() const {
      return is_valid(DistinctFormalParametersProduction);
    }

    // Note: callers should also check
    // is_valid_formal_parameter_list_without_duplicates().
    bool is_valid_strict_mode_formal_parameters() const {
      return is_valid(StrictModeFormalParametersProduction);
    }

    // Note: callers should also check is_valid_strict_mode_formal_parameters()
    // and is_valid_formal_parameter_list_without_duplicates().
    bool is_valid_strong_mode_formal_parameters() const {
      return is_valid(StrongModeFormalParametersProduction);
    }

    const Error& expression_error() const {
      return FindError(ExpressionProduction);
    }

    const Error& binding_pattern_error() const {
      return FindError(BindingPatternProduction);
    }

    const Error& assignment_pattern_error() const {
      return FindError(AssignmentPatternProduction);
    }

    const Error& arrow_formal_parameters_error() const {
      return FindError(ArrowFormalParametersProduction);
    }

    const Error& duplicate_formal_parameter_error() const {
      return FindError(DistinctFormalParametersProduction);
    }

    const Error& strict_mode_formal_parameter_error() const {
      return FindError(StrictModeFormalParametersProduction);
    }

    const Error& strong_mode_formal_parameter_error() const {
      return FindError(StrongModeFormalParametersProduction);
    }

    void RecordExpressionError(const Scanner::Location& loc,
                               MessageTemplate::Template message,
                               const char* arg = nullptr) {
      RecordError(ExpressionProduction, loc, message, arg);
    }

    void RecordBindingPatternError(const Scanner::Location& loc,
                                   MessageTemplate::Template message,
                                   const char* arg = nullptr) {
      RecordError(BindingPatternProduction, loc, message, arg);
    }

    void RecordAssignmentPatternError(const Scanner::Location& loc,
                                      MessageTemplate::Template message,
                                      const char* arg = nullptr) {
      RecordError(AssignmentPatternProduction, loc, message, arg);
    }

    void RecordArrowFormalParametersError(const Scanner::Location& loc,
                                          MessageTemplate::Template message,
                                          const char* arg = nullptr) {
      RecordError(ArrowFormalParametersProduction, loc, message, arg);
    }

    void RecordDuplicateFormalParameterError(const Scanner::Location& loc) {
      RecordError(DistinctFormalParametersProduction, loc,
                  MessageTemplate::kStrictParamDupe, nullptr);
    }

    // Record a binding that would be invalid in strict mode.  Confusingly this
    // is not the same as StrictFormalParameterList, which simply forbids
    // duplicate bindings.
    void RecordStrictModeFormalParameterError(const Scanner::Location& loc,
                                              MessageTemplate::Template message,
                                              const char* arg = nullptr) {
      RecordError(StrictModeFormalParametersProduction, loc, message, arg);
    }

    void RecordStrongModeFormalParameterError(const Scanner::Location& loc,
                                              MessageTemplate::Template message,
                                              const char* arg = nullptr) {
      RecordError(StrongModeFormalParametersProduction, loc, message, arg);
    }

    void Accumulate(const Cursor& inner,
                    unsigned productions = StandardProductions) {
      // Propagate errors from inner, but don't overwrite already recorded
      // errors.
      if (inner.invalid_productions() == 0) return;
      unsigned non_arrow_inner_invalid_productions =
          inner.invalid_productions() & ~ArrowFormalParametersProduction;
      unsigned non_arrow_productions =
          productions & ~ArrowFormalParametersProduction;
      unsigned errors =
          non_arrow_productions & non_arrow_inner_invalid_productions;
      invalid_productions_ |= errors;

      // As an exception to the above, the result continues to be a valid arrow
      // formal parameters if the inner expression is a valid binding pattern.
      if (productions & ArrowFormalParametersProduction &&
          !inner.is_valid_binding_pattern()) {
        invalid_productions_ |= ArrowFormalParametersProduction;
      }
    }

   private:
    void RecordError(TargetProduction production, const Scanner::Location& loc,
                     MessageTemplate::Template message, const char* arg) {
      if (!is_valid(production)) return;
      invalid_productions_ |= production;
      classifier_->buffer_.emplace_back(production, loc, message, arg);
    }

    const Error& FindError(TargetProduction production) const {
      CHECK(!is_valid(production));
      size_t end = classifier_->buffer_.size();
      while (true) {
        DCHECK(end > 0);
        size_t idx = end - 1;
        const BufferElement& elt = classifier_->buffer_[idx];
        if ((elt.invalid_productions() & production) == 0) {
          DCHECK(elt.skip() <= idx);
          // Hack.  All other productions propagate errors from their same
          // productions; ArrowFormalParametersProduction propagates from
          // BindingPatternProduction.
          if (production == ArrowFormalParametersProduction
              && (elt.invalid_productions() & BindingPatternProduction) != 0) {
            end = idx;
          } else {
            end = idx - elt.skip();
          }
        } else if (elt.is_leaf()) {
          return elt.error();
        } else {
          end = idx;
        }
      }
    }

    bool is_valid(TargetProduction production) const {
      return (invalid_productions() & production) == 0;
    }

    ProductionClassifier* classifier_;
    const size_t start_;
    unsigned invalid_productions_;
  };

  Cursor push() { return Cursor(this); }

 private:
  friend class Cursor;

  void pop(const Cursor& cursor) {
    DCHECK(buffer_.size() >= cursor.start());
    if (buffer_.size() == cursor.start()) {
      DCHECK(cursor.invalid_productions() == 0);
      return;
    }
    if (cursor.invalid_productions() == 0) {
      buffer_.resize(cursor.start());
    } else {
      DCHECK(buffer_.size() > cursor.start());
      size_t skip = buffer_.size() - cursor.start();
      buffer_.emplace_back(cursor.invalid_productions(), skip);
    }
  }

  ZoneVector<BufferElement> buffer_;
};


} }  // v8::internal

#endif  // V8_PRODUCTION_CLASSIFIER_H
