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
    int base_;   // Memory Start
    int size_;   // Memory Size
    char *ram_;  // Memory Content
    bool checkRange(int address);
    
public:
    RAM();
    RAM(const int base, const int length);
    ~RAM();
    const int& size();
    const int& base();
    RunCode readByte(int address, char *dest);
    RunCode readWord(int address, int *dest);
    RunCode read(int address, char *data, int len);
    RunCode write(int address, char *data, int len);
    RunCode writeByte(int address, char data);
    RunCode writeWord(int address, int data);
    void show();
};

#endif /* Memory_hpp */
