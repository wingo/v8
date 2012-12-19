// Copyright 2012 the V8 project authors. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "v8.h"

#include "objects.h"
#include "string-stream.h"
#include "utils-inl.h"

#ifdef __GNUC__
#define LIKELY(x) __builtin_expect((x), 1)
#define UNLIKELY(x) __builtin_expect((x), 0)
#else
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#endif

namespace v8 {
namespace internal {


#include "code-table.inc.c"


class CompressedSourceCodec {
 public:
  // A compressed source cursor is an offset into a bytevector, plus an offset
  // into the first token.
  class Cursor {
  public:
    Cursor(unsigned byte_offset, unsigned sub_token_offset)
        : byte_offset_(byte_offset)
        , sub_token_offset_(sub_token_offset) {
    }

    unsigned byte_offset() const { return byte_offset_; }
    void set_byte_offset(unsigned offset) { byte_offset_ = offset; }

    unsigned sub_token_offset() const { return sub_token_offset_; }
    void set_sub_token_offset(unsigned offset) { sub_token_offset_ = offset; }

  private:
    unsigned byte_offset_;
    unsigned sub_token_offset_;
  };


  static const unsigned kCharsPerIndexEntry = 1024;

  static const unsigned kAsciiCode = 0;
  static const unsigned kUnicodeCode = 1;
  static const unsigned kFirstBytecode = 2;
  static const unsigned kLastBytecode = 255;
  static const unsigned kMaxTokenLength = 9;

  STATIC_ASSERT(sizeof(token_lengths) == kLastBytecode + 1);
  STATIC_ASSERT(kFirstBytecode > kUnicodeCode);
  STATIC_ASSERT(kFirstBytecode > kAsciiCode);

  static unsigned IndexSize(unsigned length) {
    ASSERT(IsPowerOf2(kCharsPerIndexEntry));
    return (length / kCharsPerIndexEntry) * kIntSize;
  }

  static void WriteIndex(Vector<uint8_t> index, unsigned pos,
                         unsigned byte_offset) {
    ASSERT(pos >= kCharsPerIndexEntry);
    ASSERT(!(pos % kCharsPerIndexEntry));
    unsigned entry = pos / kCharsPerIndexEntry - 1;
    memcpy(index.start() + entry * kIntSize, &byte_offset, kIntSize);
  }

  // Unlike WriteIndex, which takes an index vector directly, ReadIndex assumes
  // that the index data has been appended to the compressed data.
  static unsigned ReadIndex(const Vector<uint8_t> data, unsigned pos,
                            unsigned length) {
    if (pos < kCharsPerIndexEntry)
      return 0;
    uint8_t* index_base = data.start() + data.length() - IndexSize(length);
    unsigned entry = pos / kCharsPerIndexEntry - 1;
    unsigned offset;
    memcpy(&offset, index_base + entry * kIntSize, kIntSize);
    return offset;
  }

  static void Encode(Handle<String> input, Collector<uint8_t>* output,
                     Vector<uint8_t> index) {
    // These assertions are only needed here and not in the rest of this class
    // because we will have to Encode() before we do anything on encoded data.
    ASSERT(token_lengths[kAsciiCode] == 1);
    ASSERT(token_lengths[kUnicodeCode] == 1);
    ASSERT(token_lengths[kFirstBytecode] <= token_lengths[kLastBytecode]);
    ASSERT(token_lengths[kLastBytecode] == kMaxTokenLength);

    input->TryFlatten();
    String::FlatContent content = input->GetFlatContent();
    if (content.IsAscii())
      EncodeFlatAscii(content.ToAsciiVector(), output, index);
    else if (content.IsTwoByte())
      EncodeFlatTwoByte(content.ToUC16Vector(), output, index);
    else
      EncodeNotFlat(*input, output, index);
  }

  template <typename T>
  static void Decode(Vector<uint8_t> data, Cursor cursor, Vector<T> dest) {
    // With GCC and -O3, I get a few percent performance improvements by using
    // pointers instead of going through vectors.  It's nasty but speed is
    // important here.
    const uint8_t* data_ptr = data.start();
    const uint8_t* data_end = data_ptr + data.length();
    T* dest_ptr = dest.start();
    const T* dest_end = dest_ptr + dest.length();

    data_ptr += cursor.byte_offset();

    if (cursor.sub_token_offset()) {
      uint8_t code;
      T first_token[kMaxTokenLength];
      unsigned decoded_chars = 0;

      ASSERT(token_lengths[255] == kMaxTokenLength);
      ASSERT(cursor.sub_token_offset() < kMaxTokenLength);
      ASSERT(data_ptr < data_end);
      USE(data_end);

      code = *data_ptr++;

      if (is_bytecode(code)) {
        decoded_chars = decode_bytecode(code, first_token, kMaxTokenLength);
      } else if (is_ascii(code)) {
        UNREACHABLE();
        ASSERT(data_ptr < data_end);
        decoded_chars = 1;
        first_token[0] = *data_ptr++;
      } else {
        ASSERT(is_unicode(code));
        ASSERT(data_ptr + 2 < data_end);
        unsigned uc = decode_unicode(data_ptr[0], data_ptr[1], data_ptr[2]);
        decoded_chars = write_as_utf16(uc, first_token, kMaxTokenLength);
        data_ptr += 3;
      }

      ASSERT(cursor.sub_token_offset() < decoded_chars);
      decoded_chars -= cursor.sub_token_offset();
      if (decoded_chars > dest_end - dest_ptr)
        decoded_chars = dest_end - dest_ptr;

      for (unsigned i = 0; i < decoded_chars; i++)
        dest_ptr[i] = first_token[i + cursor.sub_token_offset()];

      dest_ptr += decoded_chars;
    }

    while (dest_ptr < dest_end) {
      ASSERT(data_ptr < data_end);
      uint8_t code = *data_ptr++;

      if (is_bytecode(code)) {
        dest_ptr += decode_bytecode(code, dest_ptr, dest_end - dest_ptr);
      } else if (is_ascii(code)) {
        ASSERT(data_ptr < data_end);
        *dest_ptr++ = *data_ptr++;
      } else {
        ASSERT(is_unicode(code));
        ASSERT(data_ptr + 2 < data_end);
        unsigned uc = decode_unicode(data_ptr[0], data_ptr[1], data_ptr[2]);
        data_ptr += 3;
        dest_ptr += write_as_utf16(uc, dest_ptr, dest_end - dest_ptr);
      }
    }
  }

  // The character counting is more complicated that it need be.  The source
  // compressor doesn't care about the encoding -- it can produce any kind of
  // unicode.  However for compatibility with JS strings, we count utf-16 code
  // units as separate characters.
  //
  // So the sequence goes: decode codepoints from the data; encode them as
  // utf-16; then dump the selected range of utf-16 code units as utf-8 bytes to
  // 'file'.
  static void Dump(FILE* file, Vector<uint8_t> data, Cursor cursor, int chars) {
    const uint8_t* data_ptr = data.start();
    const uint8_t* data_end = data_ptr + data.length();
    unsigned ignore = cursor.sub_token_offset();

    data_ptr += cursor.byte_offset();

    ASSERT(token_lengths[255] == kMaxTokenLength);
    ASSERT(ignore < kMaxTokenLength);

    while (chars > 0) {
      ASSERT(data_ptr < data_end);
      USE(data_end);

      uint8_t code;
      unsigned decoded_chars = 0;
      uc16 token[kMaxTokenLength];

      code = *data_ptr++;

      if (is_bytecode(code)) {
        decoded_chars = decode_bytecode(code, token, kMaxTokenLength);
      } else if (is_ascii(code)) {
        ASSERT(data_ptr < data_end);
        decoded_chars = 1;
        token[0] = *data_ptr++;
      } else {
        ASSERT(is_unicode(code));
        ASSERT(data_ptr + 2 < data_end);
        unsigned uc = decode_unicode(data_ptr[0], data_ptr[1], data_ptr[2]);
        data_ptr += 3;
        decoded_chars += write_as_utf16(uc, token, kMaxTokenLength);
      }

      ASSERT(ignore < decoded_chars);
      unsigned skip = (ignore < decoded_chars) ? ignore : decoded_chars;
      ignore -= skip;
      for (unsigned i = skip; i < decoded_chars && chars > 0; i++, chars--) {
        char buffer[unibrow::Utf8::kMaxEncodedSize];
        unsigned uc = token[i];

        if (unibrow::Utf16::IsLeadSurrogate(uc)
            && i + 1 < decoded_chars
            && chars > 1
            && unibrow::Utf16::IsTrailSurrogate(token[i+1])) {
          i++;
          chars--;
          uc = unibrow::Utf16::CombineSurrogatePair(uc, token[i]);
        }

        unsigned encoded_length = unibrow::Utf8::Encode(buffer, uc, -1);

        for (unsigned j = 0; j < encoded_length; j++)
          putc(buffer[j], file);
      }
    }

    ASSERT(chars == 0);
  }

  static void AdvanceCursor(Vector<uint8_t> data, Cursor* cursor, int chars) {
    unsigned byte_offset = cursor->byte_offset();
    int chars_written = 0;
    int prev_byte_offset = 0;
    int prev_chars_written = 0;

    chars += cursor->sub_token_offset();

    while (chars_written < chars) {
      prev_byte_offset = byte_offset;
      prev_chars_written = chars_written;

      uint8_t code = data[byte_offset++];

      chars_written += token_lengths[code];
      if (!is_bytecode(code)) {
        if (is_ascii(code)) {
          byte_offset++;
        } else {
          ASSERT(is_unicode(code));
          chars_written += uc16_length(data[byte_offset], data[byte_offset+1],
                                       data[byte_offset+2]) - 1;
          byte_offset += 3;
        }
      }
    }

    if (chars_written == chars) {
      cursor->set_byte_offset(byte_offset);
      cursor->set_sub_token_offset(0);
    } else {
      cursor->set_byte_offset(prev_byte_offset);
      cursor->set_sub_token_offset(chars - prev_chars_written);
    }
  }

  static Cursor GetCursor(const Vector<uint8_t> data, unsigned pos,
                          unsigned length) {
    Cursor cursor(ReadIndex(data, pos, length), 0);
    pos %= kCharsPerIndexEntry;
    AdvanceCursor(data, &cursor, pos);
    return cursor;
  }

  static bool IsAscii(Vector<uint8_t> data, Cursor cursor, int chars) {
    const uint8_t* data_ptr = data.start();
    const uint8_t* data_end = data_ptr + data.length();

    data_ptr += cursor.byte_offset();
    chars += cursor.sub_token_offset();

    while (chars > 0) {
      ASSERT(data_ptr < data_end);
      USE(data_end);

      uint8_t code = *data_ptr++;

      chars -= token_lengths[code];
      if (!is_bytecode(code)) {
        if (is_ascii(code)) {
          ASSERT(data_ptr < data_end);
          data_ptr++;
        } else {
          ASSERT(is_unicode(code));
          return false;
        }
      }
    }

    return true;
  }

 private:
  static void EncodeFlatAscii(Vector<const char> input,
                              Collector<uint8_t>* output,
                              Vector<uint8_t> index) {
#include "encoder.inc.c"
  }

  static void EncodeFlatTwoByte(Vector<const uc16> input,
                                Collector<uint8_t>* output,
                                Vector<uint8_t> index) {
#include "encoder.inc.c"
  }

  static void EncodeNotFlat(String* string,
                            Collector<uint8_t>* output,
                            Vector<uint8_t> index) {
    SequentialStringReader input(string);
#include "encoder.inc.c"
  }

  template<typename T>
  static unsigned decode_bytecode(uint8_t code, T* dest, unsigned dest_len) {
#define output dest, dest_len
#include "decoder.inc.c"
#undef output
  }

  // Helpers for the encoder.
  template<typename T>
  static unsigned fill_input_buffer(const T& input,
                                    int* input_buffer, unsigned pos,
                                    unsigned block_size) {
    ASSERT(block_size == kCharsPerIndexEntry);
    unsigned length = input.length();
    if (pos + block_size <= length) {
      unsigned i;
      for (i = 0; i < block_size; i++)
        input_buffer[i] = input[pos + i];
      return i;
    } else {
      unsigned i, j;
      for (i = 0; pos + i < length; i++)
        input_buffer[i] = input[pos + i];
      for (j = i; j < block_size; j++)
        input_buffer[j] = -1;
      return i;
    }
  }
  static void add_index_entry(Vector<uint8_t> index, Collector<uint8_t>* output,
                              unsigned pos) {
    ASSERT(pos % kCharsPerIndexEntry == 0);
    if (pos)
      WriteIndex(index, pos, output->size());
  }
  static void write_u8(Collector<uint8_t>* output, uint8_t byte) {
    output->Add(byte);
  }

  // Helpers for the decoder.
  static bool is_ascii(uint8_t code) { return code == kAsciiCode; }
  static bool is_unicode(uint8_t code) { return code == kUnicodeCode; }
  static bool is_bytecode(uint8_t code) { return code >= kFirstBytecode; }
  static unsigned decode_unicode(unsigned b0, unsigned b1, unsigned b2) {
    return (b0 << 16) | (b1 << 8) | b2;
  }
  template<typename T>
  static void write_chars(T* dest, unsigned max, const char* src, unsigned n) {
    if (LIKELY(n <= max)) {
      for (unsigned i = 0; i < n; i++)
        dest[i] = src[i];
    } else {
      for (unsigned i = 0; i < max; i++)
        dest[i] = src[i];
    }
  }
  static unsigned write_as_utf16(unsigned codepoint, char* dest,
                                 unsigned dest_len) {
    UNREACHABLE();
    return 0;
  }
  static unsigned write_as_utf16(unsigned codepoint, uc16* dest,
                                 unsigned dest_len) {
    if (codepoint <= unibrow::Utf16::kMaxNonSurrogateCharCode) {
      if (dest_len >= 1)
        dest[0] = static_cast<uc16>(codepoint);
      return 1;
    } else {
      ASSERT(codepoint <= unibrow::Utf16::kMaxCharCode);
      if (dest_len >= 1)
        dest[0] = unibrow::Utf16::LeadSurrogate(codepoint);
      if (dest_len >= 2)
        dest[1] = unibrow::Utf16::TrailSurrogate(codepoint);
      return 2;
    }
  }

  // Helpers for the scanner.
  static unsigned uc16_length(uint8_t b0, uint8_t b1, uint8_t b2) {
    if (decode_unicode(b0, b1, b2) < unibrow::Utf16::kMaxNonSurrogateCharCode)
      return 1;
    else
      return 2;
  }

  // Encoder helper for reading characters from non-flat strings.
  class SequentialStringReader {
   public:
    explicit SequentialStringReader(String *s)
      : buffer_(s),
        next_(0),
        length_(s->length()) { }

    unsigned operator[](unsigned index) const {
      ASSERT(next_++ == index);
      return buffer_.GetNext();
    }

    unsigned length() const {
      return length_;
    }

   private:
    mutable StringInputBuffer buffer_;
    mutable unsigned next_;
    unsigned length_;

    DISALLOW_IMPLICIT_CONSTRUCTORS(SequentialStringReader);
  };


 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(CompressedSourceCodec);
};


static CompressedSourceCodec::Cursor GetCursor(CompressedSource* source,
                                               int pos) {
  Vector<uint8_t> bv(source->bytes()->GetDataStartAddress(),
                     source->bytes()->length());
  return CompressedSourceCodec::GetCursor(bv, pos, source->char_length());
}


static void AdvanceCursor(CompressedSource* source,
                          CompressedSourceCodec::Cursor* cursor,
                          int chars) {
  Vector<uint8_t> bv(source->bytes()->GetDataStartAddress(),
                     source->bytes()->length());
  CompressedSourceCodec::AdvanceCursor(bv, cursor, chars);
}


static uc16 Get(CompressedSource* source,
                CompressedSourceCodec::Cursor cursor) {
  Vector<uint8_t> bv(source->bytes()->GetDataStartAddress(),
                     source->bytes()->length());
  EmbeddedVector<uc16, 1> chars;
  CompressedSourceCodec::Decode(bv, cursor, chars);
  return chars[0];
}


Handle<CompressedSource> CompressedSource::Compress(Handle<String> src) {
  Collector<uint8_t> out;
  unsigned index_size = CompressedSourceCodec::IndexSize(src->length());
  ScopedVector<uint8_t> index(index_size);
  Isolate* isolate = src->GetIsolate();

  CompressedSourceCodec::Encode(src, &out, index);

  unsigned compressed_size = out.size() + index_size;
  Handle<ByteArray> bytes = isolate->factory()->NewByteArray(compressed_size,
                                                             TENURED);
  Vector<uint8_t> data(bytes->GetDataStartAddress(), out.size());
  out.WriteTo(data);

  memcpy(bytes->GetDataStartAddress() + out.size(), index.start(), index_size);

#ifdef DEBUG
  CompressedSourceCodec::Cursor cursor(0, 0);
  CompressedSourceCodec::AdvanceCursor(data, &cursor, src->length());
  ASSERT(cursor.byte_offset() == static_cast<unsigned>(out.size()));
  ASSERT(cursor.sub_token_offset() == 0);
#endif

  Handle<CompressedSource> ret = isolate->factory()->NewCompressedSource(
      bytes, src);

  return ret;
}


#ifdef OBJECT_PRINT
void CompressedSource::CompressedSourcePrint(FILE* out, int start, int length) {
  Vector<uint8_t> bv(bytes()->GetDataStartAddress(),
                     bytes()->length());
  CompressedSourceCodec::Cursor cursor = GetCursor(this, start);
  CompressedSourceCodec::Dump(out, bv, cursor, length);
}
#endif


int CompressedSource::Decompress(int start, int length, StringStream *dest) {
  CompressedSourceCodec::Cursor cursor = GetCursor(this, start);
  int chars_read = 0;

  while (chars_read < length) {
    uint32_t codepoint = Get(this, cursor);
    int prev_chars_read = chars_read;

    AdvanceCursor(this, &cursor, 1);
    chars_read++;

    if (unibrow::Utf16::IsLeadSurrogate(codepoint)
        && chars_read < length) {
      uint32_t trailing = Get(this, cursor);
      if (unibrow::Utf16::IsTrailSurrogate(trailing)) {
        AdvanceCursor(this, &cursor, 1);
        chars_read++;
        codepoint = unibrow::Utf16::CombineSurrogatePair(codepoint, trailing);
      }
    }

    char bytes[unibrow::Utf8::kMaxEncodedSize];
    int byte_length = unibrow::Utf8::Encode(bytes, codepoint, -1);
    // FIXME: no way to know if we will be able to write the whole encoded
    // sequence.
    if (!dest->Put(bytes[0]))
      return prev_chars_read;
    for (int i = 1; i < byte_length; i++)
      if (!dest->Put(bytes[i]))
        // FIXME: Error out here?
        return prev_chars_read;
  }

  return chars_read;
}


Handle<String> CompressedSource::Decompress() {
  return Decompress(0, char_length());
}


Handle<String> CompressedSource::Decompress(int start, int length) {
  if (cached_string()->IsString()) {
    Handle<String> source(String::cast(cached_string()));
    return GetIsolate()->factory()->NewSubString(source, start, start + length);
  }

  Vector<uint8_t> bv(bytes()->GetDataStartAddress(), bytes()->length());
  CompressedSourceCodec::Cursor cursor = GetCursor(this, start);

  if (CompressedSourceCodec::IsAscii(bv, cursor, length)) {
    Handle<CompressedSource> this_handle(this);
    Handle<SeqAsciiString> ret =
        GetIsolate()->factory()->NewRawAsciiString(length);
    Vector<uint8_t> bv(this_handle->bytes()->GetDataStartAddress(),
                       this_handle->bytes()->length());
    Vector<char> chars(ret->GetChars(), length);
    CompressedSourceCodec::Decode(bv, cursor, chars);
    return ret;
  } else {
    Handle<CompressedSource> this_handle(this);
    Handle<SeqTwoByteString> ret =
        GetIsolate()->factory()->NewRawTwoByteString(length);
    Vector<uint8_t> bv(this_handle->bytes()->GetDataStartAddress(),
                       this_handle->bytes()->length());
    Vector<uc16> chars(ret->GetChars(), length);
    CompressedSourceCodec::Decode(bv, cursor, chars);
    return ret;
  }
}


// If this function turns out to be hot, we can provide an optimized
// implementation.
bool CompressedSource::SubStringEquals(int start, String *other) {
  if (start + other->length() > char_length())
    return false;

  if (cached_string()->IsString()) {
    String* string =String::cast(cached_string());
    return string->SubStringEquals(start, start + other->length(), other);
  }

  CompressedSourceCodec::Cursor cursor = GetCursor(this, start);

  int chars = other->length();
  for (int i = 0;
       i < chars;
       i++, AdvanceCursor(this, &cursor, 1)) {
    if (Get(this, cursor) != other->Get(i)) return false;
  }

  return true;
}


class CompressedSourceHasher: public StringHasher {
 public:
  CompressedSourceHasher(unsigned length, uint32_t seed)
      : StringHasher(length, seed) { }

  uint32_t ComputeHash(CompressedSource* source, unsigned start,
                       unsigned length)  {
    if (!has_trivial_hash()) {
      Vector<uint8_t> bv(source->bytes()->GetDataStartAddress(),
                         source->bytes()->length());
      CompressedSourceCodec::Cursor cursor = GetCursor(source, start);
      unsigned remaining = length;
      const unsigned kBufferSize = 32;
      EmbeddedVector<uc16, kBufferSize> buffer;

      while (remaining) {
        unsigned count = (remaining < kBufferSize) ? remaining : kBufferSize;
        Vector<uc16> chars = buffer.SubVector(0, count);

        CompressedSourceCodec::Decode(bv, cursor, chars);
        AddCharacters(chars.start(), count);
        CompressedSourceCodec::AdvanceCursor(bv, &cursor, count);

        remaining -= count;
      }
    }

    return GetHashField();
  }

 protected:
  void AddCharacters(const uc16* chars, int length) {
    int i = 0;
    if (is_array_index()) {
      for (; i < length; i++)
        AddCharacter(chars[i]);
    } else {
      for (; i < length; i++)
        AddCharacterNoIndex(chars[i]);
    }
  }

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(CompressedSourceHasher);
};


uint32_t CompressedSource::SubStringHash(int start, int length) {
  ASSERT(start + length <= char_length());

  if (start == 0 && length == char_length())
    return hash();

  if (cached_string()->IsString()) {
    return String::cast(cached_string())->SubStringHash(start, start + length);
  } else {
    CompressedSourceHasher hasher(length, GetHeap()->HashSeed());
    return hasher.ComputeHash(this, start, length);
  }
}


int CompressedSource::GetLineNumberSlow(int pos) {
  int line = 0;
  CompressedSourceCodec::Cursor cursor(0, 0);
  if (pos > char_length())
    pos = char_length();
  while (pos-- > 0) {
    uc16 c = Get(this, cursor);
    AdvanceCursor(this, &cursor, 1);
    if (c == '\n') {
      line++;
    }
  }
  return line;
}


} }  // namespace v8::internal
