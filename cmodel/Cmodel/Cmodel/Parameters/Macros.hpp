//
//  Macros.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#ifndef Macros_hpp
#define Macros_hpp

//#define MEMDEBUG
#define FETCHDEBUG

#include <assert.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

// Format HEX, Format BIN
#define FHEX_PAD std::right << std::setw(8) << std::setfill('0')
#define FHEX(x) "0x" << std::hex << FHEX_PAD << x << std::dec
#define FHEXI(x) std::hex << FHEX_PAD << x << std::dec // Instruction print, exact match with .dump
#define FHEXC(x) std::hex << x << std::dec // Clean print - no padding, no prefix
#define FBIN(x,num) "0b" << std::bitset<num>(x)

#endif /* Macros_hpp */
