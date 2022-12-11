//
//  Fetch.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#ifndef Fetch_hpp
#define Fetch_hpp

#include "Macros.hpp"
#include "Consts.hpp"
#include "Interfaces.hpp"
#include "InstructionBlock.hpp"

// Fetch Unit
class FU {
private:
    if_intf_t* if_intf;
    
public:
    FU(if_intf_t* intf);
    RunCode update();
};

#endif /* Fetch_hpp */
