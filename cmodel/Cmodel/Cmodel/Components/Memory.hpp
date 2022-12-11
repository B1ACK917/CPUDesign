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
    uint64_t base_;   // Memory Start
    uint64_t size_;   // Memory Size
    u_char *ram_;  // Memory Content
    bool checkRange(uint64_t address);
    
public:
    RAM();
    RAM(const uint64_t base, const uint64_t length);
    ~RAM();
    const uint64_t& size();
    const uint64_t& base();
    RunCode readByte(uint64_t address, u_char *dest);
    RunCode readWord(uint64_t address, uint32_t *dest);
    RunCode read(uint64_t address, u_char *data, uint64_t len);
    RunCode write(uint64_t address, u_char *data, uint64_t len);
    RunCode writeByte(uint64_t address, u_char data);
    RunCode writeWord(uint64_t address, uint32_t data);
    void show();
};

#endif /* Memory_hpp */
