//
//  main.cpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/10.
//

#include "Macros.hpp"
#include "Consts.hpp"
#include "Func.hpp"

#include "test.hpp"

void test() {
    TestUnit u;
    u.run();
}

int main(int argc, const char *argv[]) {
    auto RAM_=InitDRAMFromFile(DEFAULT_HEX_FILE);
    if(!RAM_) {
        cout<<"Memory Load Failed"<<endl;
        return -1;
    }
    
#ifdef CDEBUG
    RAM_->show();
#endif
    
    for(auto t=0;t<MAX_TICK;++t) {
        ;
    }
}
