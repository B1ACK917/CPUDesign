//
//  Decode.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "Decode.hpp"

Decoder::Decoder(id_intf_t* intf) {
    this->id_intf=intf;
}

RunCode Decoder::update() {
    StaticInsn instr(id_intf->instruction_in);
    switch (instr.opcode()) {
        case OpcodeLoadFp:
            ;
            break;
            
        default:
            break;
    }
    return Success;
}
