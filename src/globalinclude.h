#pragma once
#include "QDebug"

#define BIT_CHECK(number, bitPos) ((number) &   (1ULL<<(bitPos)))
#define BIT_SET(number, bitPos)   ((number) |=  (1ULL<<(bitPos)))
#define BIT_CLEAR(number, bitPos) ((number) &= ~(1ULL<<(bitPos)))
#define BIT_FLIP(number, bitPos)  ((number) ^=  (1ULL<<(bitPos)))

#define NUMBER_OF_BITS 64
#define MAKE_TESTABLE friend class Tests;

namespace Calc {

enum NumeralSystem{
    Hex,
    Dec,
    Oct,
    Bin
};

enum BitPrecision{
    _64bit,
    _32bit,
    _16bit,
    _8bit
};

enum Functions{
    _none,
    _mod,   // 2 args
    _parOpen,  // ??
    _parClose, // ??
    _rol,   // 1 arg
    _ror,   // 1 arg
    _or,    // 2 arg
    _xor,   // 2 arg
    _lsh,   // 2 arg
    _rsh,   // 2 arg
    _not,   // 1 arg
    _and,   // 2 arg
    _invert,// 1 arg
    _divide,// 2 arg
    _multiply, // 2 arg
    _subtract, // 2 arg
    _add,      // 2 arg
    _equal  // ???
};

enum NumberPad{
    _0 = 0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    _A,
    _B,
    _C,
    _D,
    _E,
    _F,
    _backSpace,
    _clear,     // Clears all but memory
    _clearEnter // Clears number on display only
};

enum MemoryFunctions{
    _memClear,
    _memRestore,
    _memSave,
    _memAdd,
    _memSubtract
};

}

