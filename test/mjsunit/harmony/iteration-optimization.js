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

// Flags: --harmony --allow-natives-syntax

// Test Crankshaft for-of support.

function* integers_until(n) {
  for (var i = 0; i < n; i++)
    yield i;
}

function sum(iter) {
  var sum = 0;
  for (var x of iter) sum += x;
  return sum;
}

assertEquals(45, sum(integers_until(10)));

%OptimizeFunctionOnNextCall(sum);

assertEquals(45, sum(integers_until(10)));
assertTrue(%GetOptimizationStatus(sum) != 2);

assertEquals(4950, sum(integers_until(100)));
assertTrue(%GetOptimizationStatus(sum) != 2);

// If iter is null or undefined, the loop gets skipped without deoptimization.
assertEquals(0, sum(undefined));
assertTrue(%GetOptimizationStatus(sum) != 2);
assertEquals(0, sum(null));
assertTrue(%GetOptimizationStatus(sum) != 2);

assertEquals(45, sum(integers_until(10)));
assertTrue(%GetOptimizationStatus(sum) != 2);
