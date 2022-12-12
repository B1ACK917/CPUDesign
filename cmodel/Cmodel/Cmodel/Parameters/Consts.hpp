//
//  Consts.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#ifndef Consts_hpp
#define Consts_hpp

#include <string>
using std::string;
#include <vector>

// Type Definition

// Const
constexpr int BIT_WIDTH = 64;
// constexpr int DEFAULT_RAM_BASE = 0;
constexpr int DEFAULT_RAM_BASE = 0x80000000;
constexpr int DEFAULT_RAM_SIZE = 16384;
constexpr char DEFAULT_HEX_FILE[] =
"/Users/cyberdz/RIOS/lab2/cmodel/Cmodel/Cmodel/hex/add.hex";
constexpr int MAX_TICK = 3e4;

// Execption
enum RunCode {
    Success,
    MemoryViolationExecption,
    FileNotExistsExecption,
    MemoryLoadExecption,
    PCGenExecption,
    FetchExecption,
    DecodeExecption
};

// Instruction Ctrl Type
enum RegType_t{
    NONE, INT, FLOAT
};

enum CFIType {
    TYPE_NOCFI = 0,
    TYPE_BRANCH,
    TYPE_JALR,
    TYPE_JAL,
    TYPE_CBRANCH,
    TYPE_CJ,    // jal x0, offset
    TYPE_CJR,   // jalr x0, 0(rs1)
    TYPE_CJALR  // jalr x1, 0(rs1)
};
struct Exception_t {
    bool valid;
    uint32_t Cause;
    uint32_t Tval;
};

typedef struct {
    // pred
    bool valid;
    bool Taken;
    uint32_t Target;
    
    // history
    uint32_t globalHistory;
    uint32_t localHistory;
    uint32_t choiceHistory;
    bool localPredTaken;
    bool globalPredTaken;
    bool choiceGlobal;
    bool choiceTaken;
    std::vector<uint32_t> globalHistoryMg;
    uint32_t BHTEntryIndex;
    
    // filled by funcunit
    bool isJalr;
    bool isUncondCtrl;
    
    bool BruMisPred;     // mispred
    bool BruTaken;       // ActualTaken
    uint32_t BruTarget;  // ActualTarget
    uint32_t BruTakenTarget;
    bool BruTargetMispred;
    
} PredInfo_t;

enum funcType_t { ALU, MUL, DIV, BRU, CSR, LDU, STU, FPU, FMA };

enum fpType_t {
    NOTFP,
    FALU,
    FMUL,
    FDIV,
    FSQRT,
    FMINMAX,
    FFMA,
    FMOVE,
    FCMP,
    FSTU,
    FLDU,
    FCVT,
    FSGNI,
    FCLASS
};

struct fflags {
    bool NV;
    bool DZ;
    bool OF;
    bool UF;
    bool NX;
};

struct fcsr {
    uint32_t Frm;
    uint32_t AccruedExcp;
};

enum Predictor_Type {
    PREDTYPE_GSHARE = 0,
    PREDTYPE_TOURNAMENT,
    PREDTYPE_TOURNAMENTMG,
    PREDTYPE_BIMODE
};

enum InsnState_t {
    State_Fetch1,
    State_Fetch2,
    State_Decode,
    State_Dispatch,
    State_Issue,
    State_ReadOperand,
    State_Execute,
    State_WriteBack,
    State_Commit,
    State_Done
};

enum AguType_t { Gen_Addr, Gen_Data, Gen_Both };

// Defines
#define OpcodeLoad 0b0000011
#define OpcodeLoadFp 0b0000111
#define OpcodeCustom0 0b0001011
#define OpcodeMiscMem 0b0001111
#define OpcodeOpImm 0b0010011
#define OpcodeAuipc 0b0010111
#define OpcodeOpImm32 0b0011011
// Quadrant 1
#define OpcodeStore 0b0100011
#define OpcodeStoreFp 0b0100111
#define OpcodeCustom1 0b0101011
#define OpcodeAmo 0b0101111
#define OpcodeOp 0b0110011
#define OpcodeLui 0b0110111
#define OpcodeOp32 0b0111011
// Quadrant 2
#define OpcodeMadd 0b1000011
#define OpcodeMsub 0b1000111
#define OpcodeNmsub 0b1001011
#define OpcodeNmadd 0b1001111
#define OpcodeOpFp 0b1010011
#define OpcodeRsrvd1 0b1010111
#define OpcodeCustom2 0b1011011
// Quadrant 3
#define OpcodeBranch 0b1100011
#define OpcodeJalr 0b1100111
#define OpcodeRsrvd2 0b1101011
#define OpcodeJal 0b1101111
#define OpcodeSystem 0b1110011
#define OpcodeRsrvd3 0b1110111
#define OpcodeCustom3 0b1111011

#endif /* Consts_hpp */
