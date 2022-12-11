//
//  Func.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#include "Func.hpp"

RAM* InitDRAMFromFile(string filename) {
    RAM* _r=new RAM(DEFAULT_RAM_BASE,DEFAULT_RAM_SIZE);
    if(LoadHexToRAM(filename, *_r)==Success)
        return _r;
    else
        return nullptr;
}

RunCode LoadHexToRAM(string hexfile,RAM& dest) {
    ifstream file;
    file.open(hexfile);
    if(!file.is_open()) {
        cerr<<"File Not Exist"<<endl;
        return FileNotExistsExecption;
    }
    u_char readByte[3],trueByte;
    int byteCnt=0;
    auto RAMBase=dest.base();
    while(file>>readByte[0]) {
        file>>readByte[1];
        trueByte=strtol((const char*)readByte, NULL, 16);
//        cout<<std::bitset<8>(readByte[0])<<endl;
//        cout<<std::bitset<8>(readByte[1])<<endl;
//        cout<<std::bitset<8>(trueByte)<<endl;
        if(dest.writeByte(RAMBase+byteCnt, trueByte)==Success)
            ++byteCnt;
        else
            return MemoryLoadExecption;
    }
    return Success;
}
