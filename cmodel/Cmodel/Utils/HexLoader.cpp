//
//  HexLoader.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#include "HexLoader.hpp"

RunCode LoadHexToRAM(string hexfile,RAM& dest) {
    ifstream file;
    file.open(hexfile);
    if(!file.is_open()) {
        cerr<<"File Not Exist"<<endl;
        return FileNotExistsExecption;
    }
    char readByte;
    int byteCnt=0;
    auto RAMBase=dest.base();
    while(file>>readByte) {
        dest.writeByte(RAMBase+byteCnt, readByte);
        ++byteCnt;
    }
    return Success;
}
