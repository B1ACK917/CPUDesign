#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <svdpi.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

int preg[64] = {0};
extern "C" {
extern void reg_monitor(svLogic alu_valid, svLogic lsu_valid, int alu_data_in,
                        int lsu_data_in, int alu_address, int lsu_address) {
    if (alu_valid & (alu_address != 0)) {
        // printf("reg %d changed. %d -> %d\n",alu_address,preg[alu_address],alu_data_in);
        preg[alu_address] = alu_data_in;
    }
    if (lsu_valid & (lsu_address != 0)) {
        // printf("reg %d changed. %d -> %d\n",lsu_address,preg[lsu_address],lsu_data_in);
        preg[lsu_address] = lsu_data_in;
    }
    preg[0] = 0;
    return;
}

extern void rcu_monitor(svLogic rob_cm_valid, int rob_cm_exp_pc, int co_rob_rd,
                        int co_prf_name) {
    if (rob_cm_valid) {
        printf("0x%08X\n", rob_cm_exp_pc);
        if (co_rob_rd) {
            printf("x%d <- %d\n", co_rob_rd, preg[co_prf_name]);
        }
    }
    return;
}

extern void inst_log(int instruction) {
    // printf("0x%08X\n", instruction);
    return;
}
}