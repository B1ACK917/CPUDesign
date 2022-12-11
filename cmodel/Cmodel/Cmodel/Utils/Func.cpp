//
//  Func.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#include "Func.hpp"

RAM* InitDRAMFromFile(string filename) {
    RAM* _r=new RAM(DEFAULT_RAM_BASE,RAM_SIZE);
    if(LoadHexToRAM(filename, *_r)==Success)
        return _r;
    else
        return nullptr;
}
