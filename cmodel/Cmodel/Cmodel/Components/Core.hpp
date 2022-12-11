//
//  Core.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#ifndef Core_hpp
#define Core_hpp

#include "Macros.hpp"
#include "Consts.hpp"
#include "Bus.hpp"
#include "Decode.hpp"


class CPU {
private:
    uint64_t reg_[32];
    uint64_t pc_;
    BUS* bus_;
    
public:
    CPU();
    RunCode BindBUS(BUS* bus);
    RunCode Fetch(uint32_t* instruction);
    RunCode Decode(uint32_t instruction);
};



#endif /* Core_hpp */
