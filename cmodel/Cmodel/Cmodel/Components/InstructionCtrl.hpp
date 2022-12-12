//
//  InstructionCtrl.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/12.
//

#ifndef InstructionCtrl_hpp
#define InstructionCtrl_hpp

#include "Consts.hpp"
#include "Macros.hpp"

#define BRU_JAL 0
#define BRU_JALR 1
#define BRU_BEQ 2
#define BRU_BNE 3
#define BRU_BLT 4
#define BRU_BGE 5
#define BRU_BLTU 6
#define BRU_BGEU 7

#define CSR_CSRRW 0
#define CSR_CSRRS 1
#define CSR_CSRRC 2
#define CSR_CSRR 3
#define CSR_FENCEI 4
#define CSR_ECALL 5
#define CSR_EBREAK 6
#define CSR_MRET 7
#define CSR_SRET 8
#define CSR_FENCE 9
#define CSR_WFI 10
#define CSR_SFENCE 11

#define LDU_LB 0
#define LDU_LH 1
#define LDU_LW 2
#define LDU_LD 3
#define LDU_LBU 4
#define LDU_LHU 5
#define LDU_LWU 6
#define FLDU_LW 7
#define FLDU_LD 8
#define FSTU_SW 9
#define FSTU_SD 10

#define STU_SB 0
#define STU_SH 1
#define STU_SW 2
#define STU_SD 3

// FFMA
#define FMADD_S 0
#define FMADD_D 1
#define FMSUB_S 2
#define FMSUB_D 3
#define FNMSUB_S 4
#define FNMSUB_D 5
#define FNMADD_S 6
#define FNMADD_D 7

// IFMA
#define FMADD 0
#define FMHADD 1
#define FMHSUADD 2
#define FMHUADD 3

#define FMSUB 4
#define FMHSUB 5
#define FMHSUSUB 6
#define FMHUSUB 7
// #define FNMSUB        8
// #define FNMADD        9

// FALU, need to classify later
#define FADD_S 8
#define FSUB_S 9
#define FMUL_S 10
#define FDIV_S 11
#define FSQRT_S 12
#define FSGNJ_S 13
#define FSGNJN_S 14
#define FSGNJX_S 15
#define FMIN_S 16
#define FMAX_S 17
#define FCVT_W_S 18
#define FCVT_WU_S 19
#define FMV_X_W 20
#define FEQ_S 21
#define FLT_S 22
#define FLE_S 23
#define FCLASS_S 24
#define FCVT_S_W 25
#define FCVT_S_WU 26
#define FMV_W_X 27
#define FADD_D 28
#define FSUB_D 29
#define FMUL_D 30
#define FDIV_D 31
#define FSQRT_D 32
#define FSGNJ_D 33
#define FSGNJN_D 34
#define FSGNJX_D 35
#define FMIN_D 36
#define FMAX_D 37
#define FCVT_S_D 38
#define FCVT_D_S 39
#define FEQ_D 40
#define FLT_D 41
#define FLE_D 42
#define FCLASS_D 43
#define FCVT_W_D 44
#define FCVT_WU_D 45
#define FCVT_D_W 46
#define FCVT_D_WU 47

#define ALU_ADD 0
#define ALU_SUB 1
#define ALU_SLL 2
#define ALU_SLT 3
#define ALU_SLTU 4
#define ALU_XOR 5
#define ALU_SRL 6
#define ALU_SRA 7
#define ALU_OR 8
#define ALU_AND 9

#define ALU_ADDW 10
#define ALU_SUBW 11
#define ALU_SLLW 12
#define ALU_SRLW 13
#define ALU_SRAW 14

#define MUL_MUL 0
#define MUL_MULH 1
#define MUL_MULHSU 2
#define MUL_MULHU 3

#define MUL_MULW 4

#define DIV_DIV 0
#define DIV_DIVU 1
#define DIV_REM 2
#define DIV_REMU 3

#define DIV_DIVW 4
#define DIV_DIVUW 5
#define DIV_REMW 6
#define DIV_REMUW 7

struct InstructionCtrl {
    bool valid;
    
    uint32_t Pc;
    uint32_t RobTag;
    uint32_t NearestCtrl;
    uint32_t LSQTag;
    
    funcType_t Fu;
    fpType_t FpType;
    
    uint8_t SubOp;
    
    bool IsRvcInsn;
    uint32_t CompressedInsn;
    uint32_t UncompressedInsn;
    
    bool ControlFlowInsn;
    bool IsAmoInsn;
    // bool         IsSingleIssue;
    
    uint32_t IsaRs1;
    uint32_t IsaRs2;
    uint32_t IsaRs3;
    uint32_t IsaRd;
    
    uint32_t Rs1Type;
    uint32_t Rs2Type;
    uint32_t Rs3Type;
    uint32_t RdType;
    
    uint32_t PhyRs1;
    uint32_t PhyRs2;
    uint32_t PhyRs3;
    uint32_t PhyRd;
    uint32_t LPhyRd;
    
    bool Operand1Ready;
    bool Operand2Ready;
    bool Operand3Ready;
    
    uint32_t Operand1;
    uint32_t Operand2;
    uint32_t Operand3;
    uint32_t RdResult;
    
    /* AGU Information */
    uint32_t Agu_addr;
    bool Agu_addr_ready;
    uint32_t Agu_data;
    bool Agu_data_ready;
    
    CFIType cfiType;
    uint32_t imm;
    
    fcsr Fcsr;
    
    Exception_t Excp;
    PredInfo_t Pred;
    
    uint32_t RasTop;
    uint32_t RasNext;
};

#endif /* InstructionCtrl_hpp */
