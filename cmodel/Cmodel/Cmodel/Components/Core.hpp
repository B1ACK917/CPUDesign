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
#include "PCGen.hpp"
#include "Fetch.hpp"
#include "Decode.hpp"


class CPU {
private:
    uint32_t reg_[32];
    uint32_t pc_;
    BUS* bus_;
    PCGenarator* pc_gen_;
    pc_gen_intf_t* pc_gen_intf;
    FU* fetch_;
    if_intf_t* if_intf;
    Decoder* decode_;
    id_intf_t* id_intf;
    
public:
    CPU();
    ~CPU();
    RunCode BindBUS(BUS* bus);
    RunCode BindPCGen(PCGenarator* pcg);
    RunCode BindFU(FU* fu);
    RunCode GenPC();
    RunCode Fetch();
    RunCode Decode();
};



#endif /* Core_hpp */
