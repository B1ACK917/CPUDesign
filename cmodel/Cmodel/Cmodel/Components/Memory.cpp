//
//  Memory.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#include "Memory.hpp"

RAM::RAM(const int base, const int length) {
    this->base_ = base;
    this->size_ = length;
    this->ram_ = new char[length];
    
    memset(ram_, 0, length);
}

RAM::~RAM() { delete[] this->ram_; }

const int& RAM::size() { return size_; }

const int& RAM::base() { return base_; }

bool RAM::checkRange(int address) {
    return address >= this->base_ && address < this->base_+size_;
}

RunCode RAM::readByte(int address, char* dest) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    *dest = *(ram_ + (address - base_));
    return Success;
}

RunCode RAM::readWord(int address, int* dest) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    *dest = *(int*)(ram_ + (address - base_));
    return Success;
}

RunCode RAM::read(int address, char* data, int len) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    memcpy(data, ram_ + address - base_, len);
    return Success;
}

RunCode RAM::write(int address, char* data, int len) {
    if (!checkRange(address) || !checkRange(address+len)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    memcpy(ram_ + address - base_, data, len);
    return Success;
}

RunCode RAM::writeByte(int address, char data) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    memcpy(ram_ + address - base_, &data, sizeof(char));
    return Success;
}

RunCode RAM::writeWord(int address, int data) {
    if (!checkRange(address)) {
        cerr << "Invalid Address" << endl;
        return MemoryViolationExecption;
    }
    memcpy(ram_ + address - base_, &data, sizeof(int));
    return Success;
}

void RAM::show() {
    cout<<"-------RAM Content Start-------"<<endl;
    for(auto i=base_,cnt=1;i<size_;++i,++cnt) {
        cout<<*(ram_ + (i - base_));
        if(cnt%(BIT_WIDTH/8)==0) {
            cout<<endl;
        }
    }
    cout<<"-------RAM Content End-------"<<endl;
}
