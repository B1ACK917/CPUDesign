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

class Decoder {
private:
    id_intf_t* id_intf;
    
public:
    RunCode run(uint32_t inst_word);
    
private:
};

#endif /* Decode_hpp */
