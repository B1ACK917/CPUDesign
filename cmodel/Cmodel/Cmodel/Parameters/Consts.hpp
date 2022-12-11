//
//  Consts.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#ifndef Consts_hpp
#define Consts_hpp

#include "string"
using std::string;

// Type Definition

// Const
constexpr int BIT_WIDTH = 64;
constexpr int DEFAULT_RAM_BASE = 0;
constexpr int RAM_SIZE = 16384;
constexpr char DEFAULT_HEX_FILE[] = "/Users/cyberdz/RIOS/lab2/cmodel/Cmodel/Cmodel/hex/add.hex";
constexpr int MAX_TICK = 3e4;

// Execption
enum RunCode { Success,
    MemoryViolationExecption,
    FileNotExistsExecption,
    MemoryLoadExecption
};

#endif /* Consts_hpp */
