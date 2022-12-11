//
//  InstructionBlock.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#ifndef InstructionBlock_hpp
#define InstructionBlock_hpp

#include "Macros.hpp"

class InstructionBlock{
private:
    uint32_t m_insn;

public:
    InstructionBlock(uint32_t insn);
    ~InstructionBlock();

    uint8_t rs1();
    uint8_t rs2();
    uint8_t rs3();
    uint8_t rd();
    uint32_t opcode();
    uint32_t func3();
    uint32_t func7();
    uint32_t func5();
    int32_t iimm();

    int32_t simm();
    int32_t sbimm();
    int32_t uimm();
    int32_t ujimm();
    int32_t shamt();
    uint64_t csr();
    int32_t rvc_b_imm();
    int32_t rvc_j_imm();
    
    uint32_t operator()(const uint8_t pos){
        return (this->m_insn & ((uint64_t)1 << pos)) >> pos;
    };
    uint32_t operator()(const uint8_t upper, const uint8_t lower){
        return ( ( this->m_insn & (((uint64_t)1 << (upper+1)) - 1) ) & ~(((uint64_t)1 << lower) - 1) ) >> lower;
    };
};

#endif /* InstructionBlock_hpp */
