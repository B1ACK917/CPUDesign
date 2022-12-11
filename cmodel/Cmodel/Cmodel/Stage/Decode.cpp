//
//  Decode.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "Decode.hpp"

RunCode Decoder::run(uint32_t inst_word) {
    StaticInsn instr(inst_word);
    switch (instr.opcode()) {
        case OpcodeLoadFp:
            ;
            break;
            
        default:
            break;
    }
    return Success;
}
