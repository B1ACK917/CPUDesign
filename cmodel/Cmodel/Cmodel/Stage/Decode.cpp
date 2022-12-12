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
    InstructionBlock instr(id_intf->instruction_in);
    InstructionCtrl insn;
    
    switch (instr.opcode()) {
        case OpcodeSystem:
#ifdef DECODE_DEBUG
            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
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
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    if(instr.rs2()==0)
                        cout<<"beqz"<<FRHI(instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
                    else
                        cout<<"beq"<<FRRHI(instr.rs2(), instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
#endif
                    break;
                case 0b001:
                    insn.SubOp = BRU_BNE;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    if(instr.rs2()==0)
                        cout<<"bnez"<<FRHI(instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
                    else
                        cout<<"bne"<<FRRHI(instr.rs2(), instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
#endif
                    break;
                case 0b100:
                    insn.SubOp = BRU_BLT;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    if(instr.rs2()==0)
                        cout<<"bltz"<<FRHI(instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
                    else
                        cout<<"blt"<<FRRHI(instr.rs2(), instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
#endif
                    break;
                case 0b101:
                    insn.SubOp = BRU_BGE;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    if(instr.rs2()==0)
                        cout<<"bgez"<<FRHI(instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
                    else
                        cout<<"bge"<<FRRHI(instr.rs2(), instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
#endif
                    break;
                case 0b110:
                    insn.SubOp = BRU_BLTU;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    if(instr.rs2()==0)
                        cout<<"bltuz"<<FRHI(instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
                    else
                        cout<<"bltu"<<FRRHI(instr.rs2(), instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
#endif
                    break;
                case 0b111:
                    insn.SubOp = BRU_BGEU;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    if(instr.rs2()==0)
                        cout<<"bgeuz"<<FRHI(instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
                    else
                        cout<<"bgeu"<<FRRHI(instr.rs2(), instr.rs1(),id_intf->pc_in+instr.sbimm())<<endl;
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
            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
            cout<<FJ(id_intf->pc_in+insn.imm)<<endl;
#endif
            break;
        case OpcodeJalr:
                insn.Fu  = funcType_t::BRU;
                insn.SubOp = BRU_JALR;
                if(instr.func3() != 0){
                    illegal_instr = true;
                }
                insn.Rs1Type = RegType_t::INT;
                insn.imm = instr.iimm();
                insn.ControlFlowInsn = true;
                insn.RdType  = RegType_t::INT;
#ifdef DECODE_DEBUG
            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
            cout<<FJR(instr.rs1())<<endl;
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
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"add"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b001:
                            insn.SubOp = ALU_SLL;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"sll"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b010:
                            insn.SubOp = ALU_SLT;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"slt"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b011:
                            insn.SubOp = ALU_SLTU;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"sltu"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b100:
                            insn.SubOp = ALU_XOR;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"xor"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b101:
                            insn.SubOp = ALU_SRL;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"srl"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b110:
                            insn.SubOp = ALU_OR;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"or"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b111:
                            insn.SubOp = ALU_AND;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"and"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
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
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"sub"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b101:
                            insn.SubOp = ALU_SRA;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"sra"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
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
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"mul"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b001:
                            insn.SubOp = MUL_MULH;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"mulh"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b010:
                            insn.SubOp = MUL_MULHSU;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"mulhsu"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b011:
                            insn.SubOp = MUL_MULHU;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"mulhu"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b100:
                            /* code */
                            insn.SubOp = DIV_DIV;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"div"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b101:
                            /* code */
                            insn.SubOp = DIV_DIVU;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"divu"<<FRRR(instr.rd(),instr.rs1(),instr.rs2())<<endl;
#endif
                            break;
                        case 0b110:
                            /* code */
                            insn.SubOp = DIV_REM;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                            cout<<"Decode rem Instruction"<<endl;
#endif
                            break;
                        case 0b111:
                            /* code */
                            insn.SubOp = DIV_REMU;
#ifdef DECODE_DEBUG
                            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
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
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    if(instr.rs1()==0)
                        cout<<"li"<<FRI(instr.rd(), instr.iimm())<<endl;
                    else
                        cout<<"addi"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    break;
                case 0b001:
                    insn.Operand2 = instr.shamt();
                    insn.SubOp = ALU_SLL;
                    if ((instr.func7() >> 1) != 0) {
                        illegal_instr = true;
                    }
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    cout<<"sll"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    break;
                case 0b010:
                    insn.SubOp = ALU_SLT;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    cout<<"slti"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    break;
                case 0b011:
                    insn.SubOp = ALU_SLTU;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    cout<<"sltui"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    break;
                case 0b100:
                    insn.SubOp = ALU_XOR;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    cout<<"xori"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    break;
                case 0b101:
                    insn.Operand2 = instr.shamt();
                    if ((instr.func7() >> 1) == 0b000000) {
                        insn.SubOp = ALU_SRL;
#ifdef DECODE_DEBUG
                        cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                        cout<<"srli"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    } else if ((instr.func7() >> 1) == 0b010000) {
                        insn.SubOp = ALU_SRA;
#ifdef DECODE_DEBUG
                        cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                        cout<<"srai"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    } else {
                        illegal_instr = true;
                    }
                    break;
                case 0b110:
                    insn.SubOp = ALU_OR;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    cout<<"ori"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    break;
                case 0b111:
                    insn.SubOp = ALU_AND;
#ifdef DECODE_DEBUG
                    cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
                    cout<<"andi"<<FRRI(instr.rs1(), instr.rd(), instr.iimm())<<endl;
#endif
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeAuipc:
#ifdef DECODE_DEBUG
            cout<<"["<<FHEX(id_intf->pc_in)<<"]      ";
            cout<<"auipc"<<FRHI(instr.rd(), instr.uimm())<<endl;
#endif
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
