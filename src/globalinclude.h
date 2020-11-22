#pragma once
#include "QDebug"

#define CHECK_BIT(var,pos) ((var >> pos) & 1UL)
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
    _mod,
    _parOpen,
    _parClose,
    _rol,
    _ror,
    _or,
    _xor,
    _lsh,
    _rsh,
    _not,
    _and,
    _invert,
    _divide,
    _multiply,
    _subtract,
    _add,
    _equal
};

enum NumberPad{
    _0,
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

