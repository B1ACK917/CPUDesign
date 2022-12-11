//
//  Memory.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#include "Memory.hpp"

RAM::RAM() {
    this->base_ = DEFAULT_RAM_BASE;
    this->size_ = DEFAULT_RAM_SIZE;
    this->ram_ = new u_char[DEFAULT_RAM_SIZE];
    memset(ram_, 0, DEFAULT_RAM_SIZE);
}

RAM::RAM(const uint64_t base, const uint64_t length) {
    this->base_ = base;
    this->size_ = length;
    this->ram_ = new u_char[length];
    memset(ram_, 0, length);
}

RAM::~RAM() { delete[] this->ram_; }

const uint64_t& RAM::size() { return size_; }

const uint64_t& RAM::base() { return base_; }

bool RAM::checkRange(uint64_t address) {
    return address >= this->base_ && address < this->base_+size_;
}

RunCode RAM::readByte(uint64_t address, u_char* dest) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    *dest = *(ram_ + (address - base_));
    return Success;
}

RunCode RAM::readWord(uint64_t address, uint32_t* dest) {
    if (!checkRange(address)) {
        cerr << "Invalid Address at "<< address << endl;
        return MemoryViolationExecption;
    }
    *dest = *(int*)(ram_ + (address - base_));
    return Success;
}

RunCode RAM::read(uint64_t address, u_char* data, uint64_t len) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    memcpy(data, ram_ + address - base_, len);
    return Success;
}

RunCode RAM::write(uint64_t address, u_char* data, uint64_t len) {
    if (!checkRange(address) || !checkRange(address+len)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    memcpy(ram_ + address - base_, data, len);
    return Success;
}

RunCode RAM::writeByte(uint64_t address, u_char data) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    memcpy(ram_ + address - base_, &data, sizeof(char));
    return Success;
}

RunCode RAM::writeWord(uint64_t address, uint32_t data) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    memcpy(ram_ + address - base_, &data, sizeof(int));
    return Success;
}

void RAM::show() {
    cout<<"-------RAM Content Start-------"<<endl;
    for(uint64_t i=base_;i<size_;i+=4) {
        uint32_t word;
        this->readWord(i, &word);
        cout<<FHEXI(word)<<endl;
    }
    cout<<"-------RAM Content End-------"<<endl;
}
