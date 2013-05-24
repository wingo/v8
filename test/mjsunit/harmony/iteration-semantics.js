// Copyright 2013 the V8 project authors. All rights reserved.
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

// Flags: --harmony-iteration --harmony-scoping --harmony-generators

// Test for-of syntax.

"use strict";

function* values() {
  for (var i = 0; i < arguments.length; i++) {
    yield arguments[i];
  }
}

function* integers_from(n) {
  while (1) yield n++;
}

// A destructive append.
function append(x, tail) {
  tail[tail.length] = x;
  return tail;
}

function sum(x, tail) {
  return x + tail;
}

// Normal termination.
function fold(cons, seed, iter) {
  for (var x of iter) {
    seed = cons(x, seed);
  }
  return seed;
}

// Tests "break".
function* take(iter, n) {
  if (n == 0) return;
  for (let x of iter) {
    yield x;
    if (--n == 0) break;
  }
}

// Tests "continue".
function* skip_every(iter, n) {
  var i = 0;
  for (let x of iter) {
    if (++i % n == 0) continue;
    yield x;
  }
}

assertEquals([1, 2, 3], fold(append, [], values(1, 2, 3)));
assertEquals(45, fold(sum, 0, take(integers_from(0), 10)));
assertEquals(90, fold(sum, 0, take(skip_every(integers_from(0), 2), 10)));

function* unreachable(iter) {
  for (let x of iter) {
    throw "not reached";
  }
}

assertEquals(0, fold(sum, 0, unreachable(null)));
assertEquals(0, fold(sum, 0, unreachable(undefined)));

assertThrows('fold(sum, 0, unreachable({}))', TypeError);
assertThrows('fold(sum, 0, unreachable("foo"))', TypeError);
assertThrows('fold(sum, 0, unreachable(37))', TypeError);
