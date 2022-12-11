//
//  Fetch.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "Fetch.hpp"

FU::FU(if_intf_t* intf) {
    this->if_intf=intf;
}

RunCode FU::update() {
    if(if_intf->valid) {
        uint32_t instruction;
        auto pc_=if_intf->pc_in;
        auto bus_=if_intf->bus_ctrl;
        auto code=bus_->readWord(pc_,&instruction);
        if_intf->instruction_out=instruction;
        return code;
    }
    return Success;
}
