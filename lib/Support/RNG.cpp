//===-- RNG.cpp -------------------------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "klee/ADT/RNG.h"
#include "klee/Support/OptionCategories.h"

using namespace klee;

namespace {
llvm::cl::opt<RNG::result_type> RNGInitialSeed(
    "rng-initial-seed", llvm::cl::init(5489U),
    llvm::cl::desc("seed value for random number generator (default=5489)"),
    llvm::cl::cat(klee::MiscCat));
}

RNG::RNG() : std::mt19937(RNGInitialSeed) { }

RNG::RNG(RNG::result_type seed) : std::mt19937(seed) {}

/* generates a random number on [0,0xffffffff]-interval */
unsigned int RNG::getInt32() {
  static_assert((min)() == 0);
  static_assert((max)() == -1u);
  return (*this)();
}

/* generates a random number on [0,0x7fffffff]-interval */
int RNG::getInt31() {
  return (int)(getInt32() >> 1U);
}

/* generates a random number on [0,1]-real-interval */
double RNG::getDoubleLR() {
  return getInt32()*(1.0/4294967295.0); 
  /* divided by 2^32-1 */ 
}

/* generates a random number on [0,1)-real-interval */
double RNG::getDoubleL() {
  return getInt32()*(1.0/4294967296.0); 
  /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double RNG::getDouble() {
  return (((double)getInt32()) + 0.5)*(1.0/4294967296.0); 
  /* divided by 2^32 */
}

float RNG::getFloatLR() {
  return getInt32()*(1.0f/4294967295.0f); 
  /* divided by 2^32-1 */ 
}
float RNG::getFloatL() {
  return getInt32()*(1.0f/4294967296.0f); 
  /* divided by 2^32 */
}
float RNG::getFloat() {
  return (getInt32() + 0.5f)*(1.0f/4294967296.0f); 
  /* divided by 2^32 */
}

bool RNG::getBool() {
  unsigned bits = getInt32();
  bits ^= bits >> 16U;
  bits ^= bits >> 8U;
  bits ^= bits >> 4U;
  bits ^= bits >> 2U;
  bits ^= bits >> 1U;
  return bits & 1U;
}
