//
//  Decode.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "Decode.hpp"

Decoder::Decoder(id_intf_t* intf) { this->id_intf = intf; }

RunCode Decoder::update() {
    bool illegal_instr = false;
    bool ecall = false;
    bool ebreak = false;
    InstructionBlock instr(id_intf->instruction_in);
    InstructionCtrl insn;
    switch (instr.opcode()) {
        case OpcodeSystem:
            insn.Fu = funcType_t::CSR;
            if (instr.func3() >> 2) {
                insn.Operand1 = instr.rs1();
                insn.Operand1Ready = true;
            } else {
                insn.Rs1Type = RegType_t::INT;
            }
            insn.imm = instr.csr();
#ifdef DECODE_DEBUG
            cout<<"Decode csr Instruction"<<endl;
#endif
            break;
        case OpcodeBranch:
            insn.Fu = funcType_t::BRU;
            insn.imm = instr.sbimm();
            insn.Rs1Type = RegType_t::INT;
            insn.Rs2Type = RegType_t::INT;
            insn.ControlFlowInsn = true;
            switch (instr.func3()) {
                case 0b000:
                    insn.SubOp = BRU_BEQ;
#ifdef DECODE_DEBUG
                    cout<<"beq"<<FRRD(instr.rs2(), instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
#endif
                    break;
                case 0b001:
                    insn.SubOp = BRU_BNE;
#ifdef DECODE_DEBUG
                    cout<<"Decode bne Instruction"<<endl;
#endif
                    break;
                case 0b100:
                    insn.SubOp = BRU_BLT;
#ifdef DECODE_DEBUG
                    cout<<"Decode blt Instruction"<<endl;
#endif
                    break;
                case 0b101:
                    insn.SubOp = BRU_BGE;
#ifdef DECODE_DEBUG
                    cout<<"Decode bge Instruction"<<endl;
#endif
                    break;
                case 0b110:
                    insn.SubOp = BRU_BLTU;
#ifdef DECODE_DEBUG
                    cout<<"Decode bltu Instruction"<<endl;
#endif
                    break;
                case 0b111:
                    insn.SubOp = BRU_BGEU;
#ifdef DECODE_DEBUG
                    cout<<"Decode bgeu Instruction"<<endl;
#endif
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeJal:
            insn.Fu = funcType_t::BRU;
            insn.SubOp = BRU_JAL;
            insn.Rs1Type = RegType_t::NONE;
            insn.imm = instr.ujimm();
            insn.ControlFlowInsn = true;
            insn.RdType = RegType_t::INT;
#ifdef DECODE_DEBUG
            cout<<FJ(id_intf->pc_in+insn.imm)<<endl;
#endif
            break;
        case OpcodeOp:
            insn.Rs1Type = RegType_t::INT;
            insn.Rs2Type = RegType_t::INT;
            insn.RdType = RegType_t::INT;
            switch (instr.func7()) {
                case 0b0000000:
                    insn.Fu = funcType_t::ALU;
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = ALU_ADD;
#ifdef DECODE_DEBUG
                            cout<<"Decode add Instruction"<<endl;
#endif
                            break;
                        case 0b001:
                            insn.SubOp = ALU_SLL;
#ifdef DECODE_DEBUG
                            cout<<"Decode sll Instruction"<<endl;
#endif
                            break;
                        case 0b010:
                            insn.SubOp = ALU_SLT;
#ifdef DECODE_DEBUG
                            cout<<"Decode slt Instruction"<<endl;
#endif
                            break;
                        case 0b011:
                            insn.SubOp = ALU_SLTU;
#ifdef DECODE_DEBUG
                            cout<<"Decode sltu Instruction"<<endl;
#endif
                            break;
                        case 0b100:
                            insn.SubOp = ALU_XOR;
#ifdef DECODE_DEBUG
                            cout<<"Decode xor Instruction"<<endl;
#endif
                            break;
                        case 0b101:
                            insn.SubOp = ALU_SRL;
#ifdef DECODE_DEBUG
                            cout<<"Decode srl Instruction"<<endl;
#endif
                            break;
                        case 0b110:
                            insn.SubOp = ALU_OR;
#ifdef DECODE_DEBUG
                            cout<<"Decode or Instruction"<<endl;
#endif
                            break;
                        case 0b111:
                            insn.SubOp = ALU_AND;
#ifdef DECODE_DEBUG
                            cout<<"Decode and Instruction"<<endl;
#endif
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b0100000:
                    insn.Fu = funcType_t::ALU;
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = ALU_SUB;
#ifdef DECODE_DEBUG
                            cout<<"Decode sub Instruction"<<endl;
#endif
                            break;
                        case 0b101:
                            insn.SubOp = ALU_SRA;
#ifdef DECODE_DEBUG
                            cout<<"Decode sra Instruction"<<endl;
#endif
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b0000001:
                    insn.Fu = (instr.func3() >> 2) ? funcType_t::DIV : funcType_t::MUL;
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = MUL_MUL;
#ifdef DECODE_DEBUG
                            cout<<"Decode mul Instruction"<<endl;
#endif
                            break;
                        case 0b001:
                            insn.SubOp = MUL_MULH;
#ifdef DECODE_DEBUG
                            cout<<"Decode mulh Instruction"<<endl;
#endif
                            break;
                        case 0b010:
                            insn.SubOp = MUL_MULHSU;
#ifdef DECODE_DEBUG
                            cout<<"Decode mulhsu Instruction"<<endl;
#endif
                            break;
                        case 0b011:
                            insn.SubOp = MUL_MULHU;
#ifdef DECODE_DEBUG
                            cout<<"Decode mulhu Instruction"<<endl;
#endif
                            break;
                        case 0b100:
                            /* code */
                            insn.SubOp = DIV_DIV;
#ifdef DECODE_DEBUG
                            cout<<"Decode div Instruction"<<endl;
#endif
                            break;
                        case 0b101:
                            /* code */
                            insn.SubOp = DIV_DIVU;
#ifdef DECODE_DEBUG
                            cout<<"Decode divu Instruction"<<endl;
#endif
                            break;
                        case 0b110:
                            /* code */
                            insn.SubOp = DIV_REM;
#ifdef DECODE_DEBUG
                            cout<<"Decode rem Instruction"<<endl;
#endif
                            break;
                        case 0b111:
                            /* code */
                            insn.SubOp = DIV_REMU;
#ifdef DECODE_DEBUG
                            cout<<"Decode remu Instruction"<<endl;
#endif
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            
            break;
        case OpcodeOpImm:
            insn.Fu = funcType_t::ALU;
            insn.Rs1Type = RegType_t::INT;
            insn.RdType = RegType_t::INT;
            insn.imm = instr.iimm();
            insn.Operand2 = instr.iimm();
            insn.Operand2Ready = true;
            switch (instr.func3()) {
                case 0b000:
                    insn.SubOp = ALU_ADD;
#ifdef DECODE_DEBUG
                    cout<<"li x"<<uint32_t(instr.rd())<<","<<insn.imm<<";"<<endl;
#endif
                    break;
                case 0b001:
                    insn.Operand2 = instr.shamt();
                    insn.SubOp = ALU_SLL;
                    if ((instr.func7() >> 1) != 0) {
                        illegal_instr = true;
                    }
                    break;
                case 0b010:
                    insn.SubOp = ALU_SLT;
                    break;
                case 0b011:
                    insn.SubOp = ALU_SLTU;
                    break;
                case 0b100:
                    insn.SubOp = ALU_XOR;
                    break;
                case 0b101:
                    insn.Operand2 = instr.shamt();
                    if ((instr.func7() >> 1) == 0b000000) {
                        insn.SubOp = ALU_SRL;
                    } else if ((instr.func7() >> 1) == 0b010000) {
                        insn.SubOp = ALU_SRA;
                    } else {
                        illegal_instr = true;
                    }
                    break;
                case 0b110:
                    insn.SubOp = ALU_OR;
                    break;
                case 0b111:
                    insn.SubOp = ALU_AND;
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        default:
            illegal_instr = true;
            break;
    }
    return Success;
}

/*
 RunCode Decoder::update() {
 InstructionBlock instr(id_intf->instruction_in);
 switch (instr.opcode()) {
 case OpcodeMadd:
 #ifdef DECODE_DEBUG
 cout<<"Decode add Instruction"<<endl;
 #endif
 break;
 case OpcodeMsub:
 #ifdef DECODE_DEBUG
 cout<<"Decode sub Instruction"<<endl;
 #endif
 break;
 case OpcodeNmsub:
 break;
 case OpcodeNmadd:
 break;
 case OpcodeOpFp:
 break;
 case OpcodeSystem:
 break;
 case OpcodeLoad:
 break;
 case OpcodeStore:
 break;
 case OpcodeLoadFp:
 #ifdef DECODE_DEBUG
 cout<<"Decode LoadFP Instruction"<<endl;
 #endif
 break;
 case OpcodeStoreFp:
 #ifdef DECODE_DEBUG
 cout<<"Decode StoreFP Instruction"<<endl;
 #endif
 break;
 case OpcodeAmo:
 break;
 case OpcodeBranch:
 break;
 case OpcodeJal:
 id_intf->jump_out=true;
 #ifdef DECODE_DEBUG
 cout<<"Decode jal Instruction"<<endl;
 #endif
 break;
 case OpcodeJalr:
 break;
 case OpcodeOp:
 break;
 case OpcodeOp32:
 break;
 case OpcodeOpImm:
 break;
 case OpcodeOpImm32:
 break;
 case OpcodeAuipc:
 break;
 case OpcodeLui:
 break;
 default:
 break;
 }
 return Success;
 }
 
 */
