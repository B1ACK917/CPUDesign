//
//  Core.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "Core.hpp"

CPU::CPU() {
    memset(this->reg_, 0, 32*sizeof(uint64_t));
    pc_=0;
    bus_=nullptr;
    pc_gen_intf=new pc_gen_intf_t;
    pc_gen_=new PCGenarator(pc_gen_intf);
    if_intf=new if_intf_t;
    fetch_=new FU(if_intf);
    id_intf=new id_intf_t;
    decode_=new Decoder(id_intf);
}

CPU::~CPU() {
    delete pc_gen_intf;
    delete pc_gen_;
    delete fetch_;
    delete if_intf;
    delete decode_;
    delete id_intf;
}

RunCode CPU::BindBUS(BUS* bus) {
    this->bus_=bus;
    return Success;
}

RunCode CPU::BindPCGen(PCGenarator* pcg) {
    this->pc_gen_=pcg;
    return Success;
}

RunCode CPU::BindFU(FU* fu) {
    this->fetch_=fu;
    return Success;
}

RunCode CPU::GenPC() {
    pc_gen_intf->prev_pc=this->pc_;
    this->pc_gen_->update(); // Use PCGen to generate correct PC
    this->pc_=pc_gen_intf->pc_out;
    return Success;
}

RunCode CPU::Fetch() {
    if_intf->valid=true;
    if_intf->bus_ctrl=this->bus_;
    if_intf->pc_in=this->pc_;
    auto rc=this->fetch_->update();
#ifdef FETCHDEBUG
    auto pc_in=if_intf->pc_in;
    auto instruction=if_intf->instruction_out;
    cout<<"Fetch Instruction ["<<FHEX(instruction)<<"] at PC {"<<FHEX(pc_in)<<"}"<<endl;
    cout<<"BIN: "<<FBIN(instruction, 32)<<endl;
#endif
    return rc;
}

RunCode CPU::Decode() {
    id_intf->pc_in=this->pc_;
    id_intf->instruction_in=if_intf->instruction_out;
    this->decode_->update();
    return Success;
}
