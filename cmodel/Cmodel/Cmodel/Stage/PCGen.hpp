//
//  PCGen.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#ifndef PCGen_hpp
#define PCGen_hpp

#include "Macros.hpp"
#include "Consts.hpp"
#include "Interfaces.hpp"

class PCGenarator {
private:
    pc_gen_intf_t* pc_gen_intf;
    
public:
    PCGenarator(pc_gen_intf_t* intf);
    RunCode update();
};

#endif /* PCGen_hpp */
