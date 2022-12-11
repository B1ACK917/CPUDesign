//
//  Core.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "Core.hpp"

CPU::CPU() {
    memset(this->reg_, 0, 32*sizeof(uint64_t));
    pc_=0;
    bus_=nullptr;
}

RunCode CPU::BindBUS(BUS* bus) {
    this->bus_=bus;
    return Success;
}

RunCode CPU::Fetch(uint32_t* instruction) {
    auto code=bus_->readWord(pc_,instruction);
    pc_+=4;
    return code;
}

RunCode CPU::Decode(uint32_t instruction) {
    return Success;
}
