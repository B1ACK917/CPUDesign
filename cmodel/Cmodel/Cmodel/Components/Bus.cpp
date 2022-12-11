//
//  Bus.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "Bus.hpp"

BUS::BUS() {
    this->ram_=nullptr;
}

RunCode BUS::Init(RAM* ram) {
    this->ram_=ram;
    return Success;
}

RunCode BUS::readByte(uint32_t address,u_char* dest) {
    return this->ram_->readByte(address, dest);
}

RunCode BUS::readWord(uint32_t address,uint32_t* dest) {
    return this->ram_->readWord(address, dest);
}

RunCode BUS::writeByte(uint32_t address, u_char data) {
    return this->ram_->writeByte(address, data);
}

RunCode BUS::writeWord(uint32_t address, uint32_t data) {
    return this->ram_->writeWord(address, data);
}
