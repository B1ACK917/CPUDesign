//
//  test.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#include "test.hpp"

void TestUnit::run() {
    RAM _r(0,65536);
    LoadHexToRAM("/Users/cyberdz/RIOS/lab2/cmodel/Cmodel/Cmodel/hex/add.hex", _r);
    _r.show();
}
