//
//  Bus.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#ifndef Bus_hpp
#define Bus_hpp

#include "Macros.hpp"
#include "Consts.hpp"
#include "Memory.hpp"

class BUS {
private:
    RAM* ram_;
    
public:
    BUS();
    RunCode Init(RAM* ram);
    RunCode readByte(uint32_t address,u_char* dest);
    RunCode readWord(uint32_t address,uint32_t* dest);
    RunCode writeByte(uint32_t address, u_char data);
    RunCode writeWord(uint32_t address, uint32_t data);
};

#endif /* Bus_hpp */
