//
//  Consts.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#ifndef Consts_hpp
#define Consts_hpp

#include <stdio.h>

// Type Definition

// Const
constexpr int bitWidth = 64;
constexpr int memSize = 65536;

// Execption
enum RunCode { Success, MemoryViolationExecption,FileNotExistsExecption };

#endif /* Consts_hpp */
