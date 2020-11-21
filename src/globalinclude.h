#pragma once
#include "QDebug"

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
    A,
    B,
    C,
    D,
    E,
    F,
    backSpace,
    Clear,     // Clears all but memory
    ClearEnter // Clears number on display only
};

enum MemoryFunctions{
    memClear,
    memRestore,
    memSave,
    memAdd,
    memSubtract
};

}

