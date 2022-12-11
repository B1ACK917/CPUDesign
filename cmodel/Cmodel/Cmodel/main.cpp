//
//  main.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#include "Macros.hpp"
#include "Consts.hpp"
#include "Func.hpp"

#include "Memory.hpp"
#include "Core.hpp"
#include "Bus.hpp"
#include "Simulator.hpp"

#include "test.hpp"

void test() {
    TestUnit u;
    u.run();
}

int main(int argc, const char *argv[]) {
    // Load hex file to RAM
    auto RAM_=InitDRAMFromFile(DEFAULT_HEX_FILE);
    if(!RAM_) {
        cout<<"Memory Load Failed"<<endl;
        return -1;
    }
    
#ifdef MEMDEBUG
    RAM_->show();
#endif
    
    //CPU
    auto CPU_=new CPU;
    if(!CPU_) {
        cout<<"CPU Init Failed"<<endl;
        return -1;
    }
    
    //BUS
    auto Bus_=new BUS;
    if(!Bus_) {
        cout<<"Bus Init Failed"<<endl;
        return -1;
    }
    
    // Init simulator
    Simulator sim_;
    sim_.SetRam(RAM_);
    sim_.SetCPU(CPU_);
    sim_.SetBus(Bus_);
    sim_.Init();
    
    for(auto t=0;t<MAX_TICK;++t) {
        if(sim_.Tick()!=Success)
            return -1;
    }
}
