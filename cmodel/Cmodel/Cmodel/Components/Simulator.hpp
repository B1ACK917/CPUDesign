//
//  Simulator.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#ifndef Simulator_hpp
#define Simulator_hpp

#include "Macros.hpp"
#include "Consts.hpp"
#include "Memory.hpp"
#include "Core.hpp"
#include "Bus.hpp"

class Simulator {
private:
    RAM* dram_;
    CPU* cpu_;
    BUS* bus_;
    bool first_tick_;
    
public:
    Simulator();
    ~Simulator();
    RunCode SetRam(RAM* ram);
    RunCode SetCPU(CPU* cpu);
    RunCode SetBus(BUS* bus);
    RAM* GetRam();
    CPU* GetCPU();
    BUS* GetBus();
    RunCode Init();
    RunCode Tick();
};

#endif /* Simulator_hpp */
