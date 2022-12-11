//
//  Simulator.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#include "Simulator.hpp"

Simulator::Simulator() {
    this->dram_=nullptr;
    this->cpu_=nullptr;
    this->bus_=nullptr;
    first_tick_=true;
}

Simulator::~Simulator() {
    if(this->dram_)
        delete dram_;
    if(this->cpu_)
        delete cpu_;
    if(this->bus_)
        delete bus_;
}

RunCode Simulator::SetRam(RAM* ram) {
    this->dram_=ram;
    return Success;
}

RunCode Simulator::SetCPU(CPU* cpu) {
    this->cpu_=cpu;
    return Success;
}

RunCode Simulator::SetBus(BUS* bus) {
    this->bus_=bus;
    return Success;
}

RAM* Simulator::GetRam() {
    return this->dram_;
}

BUS* Simulator::GetBus() {
    return this->bus_;
}

CPU* Simulator::GetCPU() {
    return this->cpu_;
}

RunCode Simulator::Init() {
    this->bus_->Init(this->dram_);
    this->cpu_->BindBUS(this->bus_);
    return Success;
}

RunCode Simulator::Tick() {
    if(!first_tick_) {
        if(this->cpu_->GenPC()!=Success) {
            cerr<<"Genarate PC Failed"<<endl;
            return PCGenExecption;
        }
    }
    
    if(this->cpu_->Fetch()!=Success) {
        cerr<<"CPU Fetch Failed"<<endl;
        return FetchExecption;
    }
    
    if(this->cpu_->Decode()!=Success) {
        cerr<<"CPU Decode Failed"<<endl;
        return DecodeExecption;
    }
    first_tick_=false;
    return Success;
}
