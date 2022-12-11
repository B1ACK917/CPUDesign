//
//  PCGen.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "PCGen.hpp"

PCGenarator::PCGenarator(pc_gen_intf_t* intf) {
    this->pc_gen_intf=intf;
}

RunCode PCGenarator::update() {
    //this->pc_gen_intf points to the signals connected to PCGenerator.
    this->pc_gen_intf->pc_out=this->pc_gen_intf->prev_pc+4;
    return Success;
}
