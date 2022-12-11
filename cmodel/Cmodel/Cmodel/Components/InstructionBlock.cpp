//
//  InstructionBlock.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "InstructionBlock.hpp"

InstructionBlock::InstructionBlock(uint32_t insn){
    this->m_insn = insn;
};

InstructionBlock::~InstructionBlock(){};

uint8_t InstructionBlock::rs1(){
    return this->operator()(19,15);
};
uint8_t InstructionBlock::rs2(){
    return this->operator()(24,20);
};
uint8_t InstructionBlock::rs3(){
    return this->operator()(31,27);
};
uint8_t InstructionBlock::rd(){
    return this->operator()(11,7);
};
uint32_t InstructionBlock::opcode(){
    return this->operator()(6,0);
};
uint32_t InstructionBlock::func3(){
    return this->operator()(14,12);
};
uint32_t InstructionBlock::func7(){
    return this->operator()(31,25);
};
uint32_t InstructionBlock::func5(){
    return this->operator()(31,27);
};
int32_t InstructionBlock::iimm(){
    return (int32_t)this->m_insn >> 20;
};

int32_t InstructionBlock::simm(){
    return (((int32_t)this->m_insn >> 31) & ~((uint32_t)((1 << 11)-1))) +
            (this->operator()(30,25) << 5) +
            (this->operator()(11,8) << 1) +
            (this->operator()(7));
};
int32_t InstructionBlock::sbimm(){
    return (((int32_t)this->m_insn >> 31) & ~((uint32_t)((1 << 12)-1))) +
            (this->operator()(7) << 11) +
            (this->operator()(30,25) << 5) +
            (this->operator()(11,8) << 1);
};
int32_t InstructionBlock::uimm(){
    return (int32_t)this->m_insn & ~((uint32_t)((1 << 12) - 1));
};
int32_t InstructionBlock::ujimm(){
    return (((int32_t)this->m_insn >> 31) & ~((uint32_t)((1 << 20)-1))) +
            (this->operator()(19,12) << 12) +
            (this->operator()(20)    << 11) +
            (this->operator()(30,25) << 5) +
            (this->operator()(24,21) << 1);
};
int32_t InstructionBlock::shamt(){
    return this->operator()(25,20);
};
uint64_t InstructionBlock::csr(){
    return this->operator()(31,20);
};
int32_t InstructionBlock::rvc_b_imm() {
    return (((int32_t)((this->operator()(12) << 8) +
            (this->operator()(11) << 4) +
            (this->operator()(10) << 3) +
            (this->operator()(6) << 7) +
            (this->operator()(5) << 6) +
            (this->operator()(4) << 2) +
            (this->operator()(3) << 1) +
            (this->operator()(2) << 5)) << 23) >> 23);
}

int32_t InstructionBlock::rvc_j_imm() {
    return (((int32_t)((this->operator()(12) << 11) +
            (this->operator()(11) << 4) +
            (this->operator()(10) << 9) +
            (this->operator()(9) << 8) +
            (this->operator()(8) << 10) +
            (this->operator()(7) << 6) +
            (this->operator()(6) << 7) +
            (this->operator()(5) << 3) +
            (this->operator()(4) << 2) +
            (this->operator()(3) << 1) +
            (this->operator()(2) << 5)) << 20) >> 20);
}
