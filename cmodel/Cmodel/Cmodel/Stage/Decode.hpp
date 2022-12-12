//
//  Decode.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#ifndef Decode_hpp
#define Decode_hpp

#include "Consts.hpp"
#include "Macros.hpp"
#include "Interfaces.hpp"
#include "InstructionBlock.hpp"
#include "InstructionCtrl.hpp"

class Decoder {
private:
    id_intf_t* id_intf;
    
public:
    Decoder(id_intf_t* intf);
    RunCode update();
};

#endif /* Decode_hpp */
