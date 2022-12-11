//
//  Memory.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#ifndef Memory_hpp
#define Memory_hpp

#include "Consts.hpp"
#include "Macros.hpp"

class RAM {
private:
    uint32_t base_;   // Memory Start
    uint32_t size_;   // Memory Size
    u_char *ram_;  // Memory Content
    bool checkRange(uint32_t address);
    
public:
    RAM();
    RAM(const uint32_t base, const uint32_t length);
    ~RAM();
    const uint32_t& size();
    const uint32_t& base();
    RunCode readByte(uint32_t address, u_char *dest);
    RunCode readWord(uint32_t address, uint32_t *dest);
    RunCode read(uint32_t address, u_char *data, uint32_t len);
    RunCode write(uint32_t address, u_char *data, uint32_t len);
    RunCode writeByte(uint32_t address, u_char data);
    RunCode writeWord(uint32_t address, uint32_t data);
    void show();
};

#endif /* Memory_hpp */
