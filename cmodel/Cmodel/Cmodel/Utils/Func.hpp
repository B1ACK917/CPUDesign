//
//  Func.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#ifndef Func_hpp
#define Func_hpp

#include "Macros.hpp"
#include "Consts.hpp"
#include "Memory.hpp"

RunCode LoadHexToRAM(string hexfile,RAM& dest);
RAM* InitDRAMFromFile(string filename);

#endif /* Func_hpp */
