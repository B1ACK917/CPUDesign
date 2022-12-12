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
        case OpcodeLoadFp:
            insn.Fu = funcType_t::LDU;
            insn.FpType = fpType_t::FLDU;
            insn.imm = instr.iimm();
            insn.Rs1Type = RegType_t::INT;
            insn.RdType = RegType_t::FLOAT;
            switch (instr.func3()) {
                case 0b010:
                    insn.SubOp = FLDU_LW;
                    break;
                case 0b011:
                    insn.SubOp = FLDU_LD;
                    break;
                default:
                    // printf("[ERROR]: Float Load Illegal.\n");
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeStoreFp:
            insn.Fu = funcType_t::STU;
            insn.FpType = fpType_t::FSTU;
            insn.imm = instr.simm();
            insn.Rs1Type = RegType_t::INT;
            insn.Rs2Type = RegType_t::FLOAT;
            switch (instr.func3()) {
                case 0b010:
                    insn.SubOp = FSTU_SW;
                    break;
                case 0b011:
                    insn.SubOp = FSTU_SD;
                    break;
                default:
                    // printf("[ERROR]: Float Store Illegal.\n");
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeMadd:
            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                illegal_instr = true;
                break;
            }
            insn.Fu = funcType_t::FPU;
            insn.Rs1Type = RegType_t::FLOAT;
            insn.Rs2Type = RegType_t::FLOAT;
            insn.Rs3Type = RegType_t::FLOAT;
            insn.RdType = RegType_t::FLOAT;
            insn.FpType = fpType_t::FFMA;
            switch (instr.func7() & 0b11) {
                case 0b00:
                    insn.SubOp = FMADD_S;
                    break;
                case 0b01:
                    insn.SubOp = FMADD_D;
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeMsub:
            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                illegal_instr = true;
                break;
            }
            insn.Fu = funcType_t::FPU;
            insn.Rs1Type = RegType_t::FLOAT;
            insn.Rs2Type = RegType_t::FLOAT;
            insn.Rs3Type = RegType_t::FLOAT;
            insn.RdType = RegType_t::FLOAT;
            insn.FpType = fpType_t::FFMA;
            switch (instr.func7() & 0b11) {
                case 0b00:
                    insn.SubOp = FMSUB_S;
                    break;
                case 0b01:
                    insn.SubOp = FMSUB_D;
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeNmsub:
            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                illegal_instr = true;
                break;
            }
            insn.Fu = funcType_t::FPU;
            insn.Rs1Type = RegType_t::FLOAT;
            insn.Rs2Type = RegType_t::FLOAT;
            insn.Rs3Type = RegType_t::FLOAT;
            insn.RdType = RegType_t::FLOAT;
            insn.FpType = fpType_t::FFMA;
            switch (instr.func7() & 0b11) {
                case 0b00:
                    insn.SubOp = FNMSUB_S;
                    break;
                case 0b01:
                    insn.SubOp = FNMSUB_D;
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeNmadd:
            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                illegal_instr = true;
                break;
            }
            insn.Fu = funcType_t::FPU;
            insn.Rs1Type = RegType_t::FLOAT;
            insn.Rs2Type = RegType_t::FLOAT;
            insn.Rs3Type = RegType_t::FLOAT;
            insn.RdType = RegType_t::FLOAT;
            insn.FpType = fpType_t::FFMA;
            switch (instr.func7() & 0b11) {
                case 0b00:
                    insn.SubOp = FNMADD_S;
                    break;
                case 0b01:
                    insn.SubOp = FNMADD_D;
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeOpFp:
            insn.Fu = funcType_t::FPU;
            switch (instr.func7()) {
                case 0b0000000:
                    if ((instr.func3() == 5) || (instr.func3() == 6)) {
                        illegal_instr = true;
                        break;
                    }
                    insn.SubOp = FADD_S;
                    insn.Rs1Type = RegType_t::FLOAT;
                    insn.Rs2Type = RegType_t::FLOAT;
                    insn.RdType = RegType_t::FLOAT;
                    insn.FpType = fpType_t::FALU;
                    break;
                case 0b0000100:
                    if ((instr.func3() == 5) || (instr.func3() == 6)) {
                        illegal_instr = true;
                        break;
                    }
                    insn.SubOp = FSUB_S;
                    insn.Rs1Type = RegType_t::FLOAT;
                    insn.Rs2Type = RegType_t::FLOAT;
                    insn.RdType = RegType_t::FLOAT;
                    insn.FpType = fpType_t::FALU;
                    break;
                case 0b0001000:
                    if ((instr.func3() == 5) || (instr.func3() == 6)) {
                        illegal_instr = true;
                        break;
                    }
                    insn.SubOp = FMUL_S;
                    insn.Rs1Type = RegType_t::FLOAT;
                    insn.Rs2Type = RegType_t::FLOAT;
                    insn.RdType = RegType_t::FLOAT;
                    insn.FpType = fpType_t::FMUL;
                    break;
                case 0b0001100:
                    if ((instr.func3() == 5) || (instr.func3() == 6)) {
                        illegal_instr = true;
                        break;
                    }
                    insn.SubOp = FDIV_S;
                    insn.Rs1Type = RegType_t::FLOAT;
                    insn.Rs2Type = RegType_t::FLOAT;
                    insn.RdType = RegType_t::FLOAT;
                    insn.FpType = fpType_t::FDIV;
                    break;
                case 0b0101100:
                    switch (instr.rs2()) {
                        case 0b00000:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FSQRT_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FSQRT;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b0010000:  // Sign Injection
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = FSGNJ_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FSGNI;
                            break;
                        case 0b001:
                            insn.SubOp = FSGNJN_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FSGNI;
                            break;
                        case 0b010:
                            insn.SubOp = FSGNJX_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FSGNI;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b0010100:
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = FMIN_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FMINMAX;
                            break;
                        case 0b001:
                            insn.SubOp = FMAX_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FMINMAX;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b1100000:
                    switch (instr.rs2()) {
                        case 0b00000:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_W_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        case 0b00001:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_WU_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b1110000:
                    switch (instr.rs2()) {
                        case 0b00000:
                            switch (instr.func3()) {
                                case 0b000:
                                    insn.SubOp = FMV_X_W;
                                    insn.Rs1Type = RegType_t::FLOAT;
                                    insn.RdType = RegType_t::INT;
                                    insn.FpType = fpType_t::FMOVE;
                                    break;
                                case 0b001:
                                    insn.SubOp = FCLASS_S;
                                    insn.Rs1Type = RegType_t::FLOAT;
                                    insn.RdType = RegType_t::INT;
                                    insn.FpType = fpType_t::FCLASS;
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
                    break;
                case 0b1010000:
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = FLE_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCMP;
                            break;
                        case 0b001:
                            insn.SubOp = FLT_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCMP;
                            break;
                        case 0b010:
                            insn.SubOp = FEQ_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCMP;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b1101000:
                    switch (instr.rs2()) {
                        case 0b00000:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_S_W;
                            insn.Rs1Type = RegType_t::INT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        case 0b00001:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_S_WU;
                            insn.Rs1Type = RegType_t::INT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b1111000:
                    switch (instr.rs2()) {
                        case 0b00000:
                            switch (instr.func3()) {
                                case 0b000:
                                    insn.SubOp = FMV_W_X;
                                    insn.Rs1Type = RegType_t::INT;
                                    insn.RdType = RegType_t::FLOAT;
                                    insn.FpType = fpType_t::FMOVE;
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
                    break;
                case 0b0000001:
                    if ((instr.func3() == 5) || (instr.func3() == 6)) {
                        illegal_instr = true;
                        break;
                    }
                    insn.SubOp = FADD_D;
                    insn.Rs1Type = RegType_t::FLOAT;
                    insn.Rs2Type = RegType_t::FLOAT;
                    insn.RdType = RegType_t::FLOAT;
                    insn.FpType = fpType_t::FALU;
                    break;
                case 0b0000101:
                    if ((instr.func3() == 5) || (instr.func3() == 6)) {
                        illegal_instr = true;
                        break;
                    }
                    insn.SubOp = FSUB_D;
                    insn.Rs1Type = RegType_t::FLOAT;
                    insn.Rs2Type = RegType_t::FLOAT;
                    insn.RdType = RegType_t::FLOAT;
                    insn.FpType = fpType_t::FALU;
                    break;
                case 0b0001001:
                    if ((instr.func3() == 5) || (instr.func3() == 6)) {
                        illegal_instr = true;
                        break;
                    }
                    insn.SubOp = FMUL_D;
                    insn.Rs1Type = RegType_t::FLOAT;
                    insn.Rs2Type = RegType_t::FLOAT;
                    insn.RdType = RegType_t::FLOAT;
                    insn.FpType = fpType_t::FMUL;
                    break;
                case 0b0001101:
                    if ((instr.func3() == 5) || (instr.func3() == 6)) {
                        illegal_instr = true;
                        break;
                    }
                    insn.SubOp = FDIV_D;
                    insn.Rs1Type = RegType_t::FLOAT;
                    insn.Rs2Type = RegType_t::FLOAT;
                    insn.RdType = RegType_t::FLOAT;
                    insn.FpType = fpType_t::FDIV;
                    break;
                case 0b0101101:
                    switch (instr.rs2()) {
                        case 0b00000:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FSQRT_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FSQRT;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b0010001:  // Sign Injection
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = FSGNJ_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FSGNI;
                            break;
                        case 0b001:
                            insn.SubOp = FSGNJN_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FSGNI;
                            break;
                        case 0b010:
                            insn.SubOp = FSGNJX_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FSGNI;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b0010101:
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = FMIN_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FMINMAX;
                            break;
                        case 0b001:
                            insn.SubOp = FMAX_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FMINMAX;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b0100000:
                    switch (instr.rs2()) {
                        case 0b00001:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_S_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b0100001:
                    switch (instr.rs2()) {
                        case 0b00000:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_D_S;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b1010001:
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = FLE_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCMP;
                            break;
                        case 0b001:
                            insn.SubOp = FLT_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCMP;
                            break;
                        case 0b010:
                            insn.SubOp = FEQ_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.Rs2Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCMP;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b1110001:
                    switch (instr.rs2()) {
                        case 0b00000:
                            insn.SubOp = FCLASS_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCLASS;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b1100001:
                    switch (instr.rs2()) {
                        case 0b00000:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_W_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        case 0b00001:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_WU_D;
                            insn.Rs1Type = RegType_t::FLOAT;
                            insn.RdType = RegType_t::INT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b1101001:
                    switch (instr.rs2()) {
                        case 0b00000:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_D_W;
                            insn.Rs1Type = RegType_t::INT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FCVT;
                            break;
                        case 0b00001:
                            if ((instr.func3() == 5) || (instr.func3() == 6)) {
                                illegal_instr = true;
                                break;
                            }
                            insn.SubOp = FCVT_D_WU;
                            insn.Rs1Type = RegType_t::INT;
                            insn.RdType = RegType_t::FLOAT;
                            insn.FpType = fpType_t::FCVT;
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
            break;
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
            switch (instr.func3() & 0b11) {
                case 0b00:
                    if (instr.rd() == 0 && instr.rs1() == 0) {
                        insn.Rs1Type = RegType_t::NONE;
                        switch (instr.iimm()) {
                            case 0b000000000000:
                                insn.SubOp = CSR_ECALL;
                                insn.ControlFlowInsn = true;
                                ecall = true;
                                break;
                            case 0b000000000001:
                                insn.SubOp = CSR_EBREAK;
                                insn.ControlFlowInsn = true;
                                ebreak = true;
                                break;
                            case 0b001100000010:
                                insn.SubOp = CSR_MRET;
                                insn.ControlFlowInsn = true;
                                break;
                            case 0b000100000010:
                                insn.SubOp = CSR_SRET;
                                insn.ControlFlowInsn = true;
                                break;
                            case 0b000100000101:
                                insn.SubOp = CSR_WFI;
                                insn.ControlFlowInsn = true;
                                break;
                            case 0b000100100000:
                                insn.SubOp = CSR_SFENCE;
                                insn.ControlFlowInsn = true;
                                break;
                            default:
                                illegal_instr = true;
                                break;
                        }
                    } else if (instr.rd() == 0) {
                        switch (instr.func7()) {
                            case 0b0001001:
                                insn.SubOp = CSR_SFENCE;
                                insn.ControlFlowInsn = true;
                                break;
                            default:
                                illegal_instr = true;
                                break;
                        }
                    } else {
                        illegal_instr = true;
                    }
                    break;
                case 0b01:
                    insn.SubOp = CSR_CSRRW;
                    insn.RdType = RegType_t::INT;
                    insn.ControlFlowInsn = true;
                    break;
                case 0b10:
                    if (instr.rs1() == 0) {
                        insn.SubOp = CSR_CSRR;
                        insn.Rs1Type = RegType_t::NONE;
                        insn.RdType = RegType_t::INT;
                        insn.ControlFlowInsn = true;
                    } else {
                        insn.SubOp = CSR_CSRRS;
                        insn.RdType = RegType_t::INT;
                        insn.ControlFlowInsn = true;
                    }
                    break;
                case 0b11:
                    if (instr.rs1() == 0) {
                        insn.SubOp = CSR_CSRR;
                        insn.Rs1Type = RegType_t::NONE;
                        insn.RdType = RegType_t::INT;
                        insn.ControlFlowInsn = true;
                    } else {
                        insn.SubOp = CSR_CSRRC;
                        insn.RdType = RegType_t::INT;
                        insn.ControlFlowInsn = true;
                    }
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeMiscMem:
            insn.Fu = funcType_t::CSR;
            insn.imm = instr.iimm();
            if (instr.rs1() == 0 && instr.rd() == 0) {
                switch (instr.func3()) {
                    case 0b000:
                        insn.Fu = funcType_t::CSR;
                        insn.SubOp = CSR_FENCE;
                        insn.ControlFlowInsn = true;
                        break;
                    case 0b001:
                        if (instr.iimm() != 0) {
                            illegal_instr = true;
                            break;
                        }
                        insn.SubOp = CSR_FENCEI;
                        insn.ControlFlowInsn = true;
                        break;
                    default:
                        break;
                }
            } else {
                illegal_instr = true;
            }
            break;
        case OpcodeLoad:
            
            insn.Fu = funcType_t::LDU;
            insn.imm = instr.iimm();
            insn.Rs1Type = RegType_t::INT;
            insn.RdType = RegType_t::INT;
            switch (instr.func3()) {
                case 0b000:
                    insn.SubOp = LDU_LB;
                    break;
                case 0b001:
                    insn.SubOp = LDU_LH;
                    break;
                case 0b010:
                    insn.SubOp = LDU_LW;
                    break;
                case 0b011:
                    insn.SubOp = LDU_LD;
                    break;
                case 0b100:
                    insn.SubOp = LDU_LBU;
                    break;
                case 0b101:
                    insn.SubOp = LDU_LHU;
                    break;
                case 0b110:
                    insn.SubOp = LDU_LWU;
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeStore:
            insn.Fu = funcType_t::STU;
            insn.imm = instr.simm();
            insn.Rs1Type = RegType_t::INT;
            insn.Rs2Type = RegType_t::INT;
            switch (instr.func3()) {
                case 0b000:
                    insn.SubOp = STU_SB;
                    break;
                case 0b001:
                    insn.SubOp = STU_SH;
                    break;
                case 0b010:
                    insn.SubOp = STU_SW;
                    break;
                case 0b011:
                    insn.SubOp = STU_SD;
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeAmo:
            insn.IsAmoInsn = true;
            switch (instr.func3()) {
                case 0b10:  // RV32A
                    switch (instr.func5()) {
                        case 0b00010:  // LR
                            insn.Fu = funcType_t::LDU;
                            insn.Rs1Type = RegType_t::INT;
                            insn.RdType = RegType_t::INT;
                            insn.SubOp = LDU_LW;
                            break;
                        case 0b00011:  // SC
                        case 0b00001:  // AMOSWAP
                        case 0b00000:  // AMOADD
                        case 0b00100:  // AMOXOR
                        case 0b01100:  // AMOAND
                        case 0b01000:  // AMOOR
                        case 0b10000:  // AMOMIN
                        case 0b10100:  // AMOMAX
                        case 0b11000:  // AMOMINU
                        case 0b11100:  // AMOMAXU
                            insn.Fu = funcType_t::STU;
                            insn.Rs1Type = RegType_t::INT;
                            insn.Rs2Type = RegType_t::INT;
                            insn.RdType = RegType_t::INT;
                            insn.SubOp = STU_SW;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                case 0b11:  // RV64A
                    switch (instr.func5()) {
                        case 0b00010:  // LR
                            insn.Fu = funcType_t::LDU;
                            insn.Rs1Type = RegType_t::INT;
                            insn.RdType = RegType_t::INT;
                            insn.SubOp = LDU_LD;
                            break;
                        case 0b00011:  // SC
                        case 0b00001:  // AMOSWAP
                        case 0b00000:  // AMOADD
                        case 0b00100:  // AMOXOR
                        case 0b01100:  // AMOAND
                        case 0b01000:  // AMOOR
                        case 0b10000:  // AMOMIN
                        case 0b10100:  // AMOMAX
                        case 0b11000:  // AMOMINU
                        case 0b11100:  // AMOMAXU
                            insn.Fu = funcType_t::STU;
                            insn.Rs1Type = RegType_t::INT;
                            insn.Rs2Type = RegType_t::INT;
                            insn.RdType = RegType_t::INT;
                            insn.SubOp = STU_SD;
                            break;
                        default:
                            illegal_instr = true;
                            break;
                    }
                    break;
                default:
                    break;
            }
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
        case OpcodeJalr:
            insn.Fu = funcType_t::BRU;
            insn.SubOp = BRU_JALR;
            if (instr.func3() != 0) {
                illegal_instr = true;
            }
            insn.Rs1Type = RegType_t::INT;
            insn.imm = instr.iimm();
            insn.ControlFlowInsn = true;
            insn.RdType = RegType_t::INT;
#ifdef DECODE_DEBUG
            cout<<"Decode jalr Instruction"<<endl;
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
        case OpcodeOp32:
            insn.Rs1Type = RegType_t::INT;
            insn.Rs2Type = RegType_t::INT;
            insn.RdType = RegType_t::INT;
            switch (instr.func7()) {
                case 0b0000000:
                    insn.Fu = funcType_t::ALU;
                    switch (instr.func3()) {
                        case 0b000:
                            insn.SubOp = ALU_ADDW;
                            break;
                        case 0b001:
                            insn.SubOp = ALU_SLLW;
                            break;
                        case 0b101:
                            insn.SubOp = ALU_SRLW;
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
                            insn.SubOp = ALU_SUBW;
                            break;
                        case 0b101:
                            insn.SubOp = ALU_SRAW;
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
                            insn.SubOp = MUL_MULW;
                            break;
                        case 0b100:
                            insn.SubOp = DIV_DIVW;
                            break;
                        case 0b101:
                            insn.SubOp = DIV_DIVUW;
                            break;
                        case 0b110:
                            insn.SubOp = DIV_REMW;
                            break;
                        case 0b111:
                            insn.SubOp = DIV_REMUW;
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
        case OpcodeOpImm32:
            insn.Fu = funcType_t::ALU;
            insn.Rs1Type = RegType_t::INT;
            insn.RdType = RegType_t::INT;
            insn.imm = instr.iimm();
            insn.Operand2 = instr.iimm();
            insn.Operand2Ready = true;
            switch (instr.func3()) {
                case 0b000:
                    insn.SubOp = ALU_ADDW;
                    break;
                case 0b001:
                    insn.Operand2 = instr.shamt();
                    insn.SubOp = ALU_SLLW;
                    if (instr.func7() != 0) {
                        illegal_instr = true;
                    }
                    break;
                case 0b101:
                    insn.Operand2 = instr.shamt();
                    if (instr.func7() == 0b0000000) {
                        insn.SubOp = ALU_SRLW;
                    } else if (instr.func7() == 0b0100000) {
                        insn.SubOp = ALU_SRAW;
                    } else {
                        illegal_instr = true;
                    }
                    break;
                default:
                    illegal_instr = true;
                    break;
            }
            break;
        case OpcodeAuipc:
            insn.Fu = funcType_t::ALU;
            insn.SubOp = ALU_ADD;
            insn.Operand1 = instr.uimm();
            insn.Operand2 = insn.Pc;
            insn.Operand1Ready = true;
            insn.Operand2Ready = true;
            insn.imm = instr.uimm();
            insn.RdType = RegType_t::INT;
            break;
        case OpcodeLui:
            insn.Fu = funcType_t::ALU;
            insn.SubOp = ALU_ADD;
            insn.Operand1 = instr.uimm();
            insn.Operand2 = 0;
            insn.Operand1Ready = true;
            insn.Operand2Ready = true;
            insn.imm = instr.uimm();
            insn.RdType = RegType_t::INT;
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
