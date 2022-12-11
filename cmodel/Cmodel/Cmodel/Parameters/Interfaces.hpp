//
//  Interfaces.hpp
//  Cmodel
//
//  Created by 冯大纬 on 2022/12/11.
//

#ifndef Interfaces_hpp
#define Interfaces_hpp

#include "Bus.hpp"

//    | is_req_pc          |  I   |  1   |       judge if btb need wirte in       |    fu     |
//    | btb_req_pc         |  I   |  32  |             btb needed pc              |    fu     |
//    | btb_predict_target |  I   |  32  |          btb needed target pc          |    fu     |
//    | prev_pc            |  I   |  32  |              pc to gshare              |    fu     |
//    | prev_branch_in     |  I   |  1   |     if this pc is a branch or jump     |    fu     |
//    | prev_taken         |  I   |  1   |        if this branch is taken         |    fu     |
//    | rd_en              |  I   |  1   | decode is ready and want a instruction |  decoder  |
//    | pc_out             |  O   |  32  |                a pc out                |  decoder  |
//    | next_pc_out        |  O   |  32  |           this pc out plus 4           |  decoder  |
//    | instruction_out    |  O   |  32  |         this pc's instruction          |  decoder  |
//    | valid_real_branch  |  I   |  1   |     if fu give a valid real branch     |    fu     |
//    | real_branch        |  I   |  32  |   this real branch or jump branch pc   |    fu     |
typedef struct {
    bool is_req_pc;
    uint32_t btb_req_pc;
    uint32_t btb_predict_target;
    uint32_t prev_pc;
    bool prev_branch_in;
    bool prev_taken;
    bool rd_en;
    uint32_t pc_out;
    uint32_t next_pc_out;
    uint32_t instruction_out;
    bool valid_real_branch;
    uint32_t real_branch;
} pc_gen_intf_t;

typedef struct {
    bool valid;
    bool rst;
    uint32_t pc_in;
    uint32_t instruction_out;
    BUS* bus_ctrl;
} if_intf_t;


//- | signal                    | I/O  | width |                 description                  | interaction  |
//  | :------------------------ | :--: | :---: | :------------------------------------------: | :----------: |
//  | clk                       |  I   |   1   |                 clock signal                 |              |
//  | rstn                      |  I   |   1   | reset signal, active low, asynchronous reset |              |
//  | pc_in                     |  I   |  32   |          get the pc from fetch unit          | instr buffer |
//  | next_pc_in                |  I   |  32   |       get the next pc from fetch unit        | instr buffer |
//  | instruction_in            |  I   |  32   |           get the instr from fetch           |    fetch     |
//  | valid_in                  |  I   |   1   |             get the valid signal             |    fetch     |
//  | ready_in                  |  I   |   1   |             get the ready signal             |     rob      |
//  | branch_back               |  I   |   1   |           handle the branch stall            |      fu      |
//  | trapped                   |  I   |   1   |               pipeline control               |      fu      |
//  | wfi_in                    |  I   |   1   |               pipeline control               |      fu      |
//  | csr_data                  |  I   |  64   |                 get csr data                 |     csr      |
//  | csr_readable              |  I   |   1   |         flag about reading from csr          |     csr      |
//  | csr_writeable             |  I   |   1   |          flag about writing to csr           |     csr      |
//  | csr_address               |  O   |  12   |                 give to csr                  |     csr      |
//  | uses_rs1                  |  O   |   1   |                   use rs1                    |     rob      |
//  | uses_rs2                  |  O   |   1   |                   use rs2                    |     rob      |
//  | uses_rd                   |  O   |   1   |                    use rd                    |     rob      |
//  | uses_csr                  |  O   |   1   |                   use csr                    |     rob      |
//  | pc_out                    |  O   |  32   |              give to rob the pc              |     rob      |
//  | next_pc_out               |  O   |  32   |           give to rob the next pc            |     rob      |
//  | is_csr                    |  O   |   1   |                flag about csr                |     rob      |
//  | write_select_out          |  O   |   2   |           write select out signal            |     rob      |
//  | rd_address_out            |  O   |   5   |                 give to rob                  |     rob      |
//  | csr_address_out           |  O   |  12   |                 give to rob                  |     rob      |
//  | mret_out                  |  O   |   1   |                 give to rob                  |     rob      |
//  | wfi_out                   |  O   |   1   |                 give to rob                  |     rob      |
//  | ecause_out                |  O   |   4   |                 give to rob                  |     rob      |
//  | exception_out             |  O   |   1   |                  exception                   |     rob      |
//  | half                      |  O   |   1   |                 give to rob                  |     rob      |
//  | valid_out                 |  O   |   1   |                  valid flag                  |     rob      |
//  | ready_out                 |  O   |   1   |             tell fecth can read              |    fetch     |
//  | csr_read_out              |  O   |   1   |                 read signal                  |     rob      |
//  | csr_write_out             |  O   |   1   |               csr write signal               |     rob      |
//  | csr_readable_out          |  O   |   1   |               csr can be read                |     rob      |
//  | csr_writeable_out         |  O   |   1   |                can write csr                 |     rob      |
//  | csr_data_out              |  O   |  64   |                  to rob alu                  |     rob      |
//  | imm_data_out              |  O   |  32   |         to rob alu about immed-data          |     rob      |
//  | alu_function_out          |  O   |   3   |                  to rob alu                  |     rob      |
//  | alu_function_modifier_out |  O   |   1   |                  to rob alu                  |     rob      |
//  | alu_select_a_out          |  O   |   2   |             alu select signal:a              |     rob      |
//  | alu_select_b_out          |  O   |   2   |             alu select signal:b              |     rob      |
//  | cmp_function_out          |  O   |   3   |           compare function signal            |     rob      |
//  | jump_out                  |  O   |   1   |                to rob branch                 |     rob      |
//  | branch_out                |  O   |   1   |                to rob branch                 |     rob      |
//  | is_alu_out                |  O   |   1   |                 to rob (lsu)                 |     rob      |
//  | load_out                  |  O   |   1   |                 to rob (lsu)                 |     rob      |
//  | store_out                 |  O   |   1   |                 to rob (lsu)                 |     rob      |
//  | load_store_size_out       |  O   |   2   |                 to rob (lsu)                 |     rob      |
//  | load_signed_out           |  O   |   1   |                 to rob (lsu)                 |     rob      |

typedef struct {
    bool rstn;
    uint32_t pc_in;
    uint32_t next_pc_in;
    uint32_t instruction_in;
    bool valid_in;
    bool ready_in;
    bool branch_back;
    bool trapped;
    bool wfi_in;
    bool uses_rs1;
    bool uses_rs2;
    bool uses_rd;
    bool uses_csr;
    uint32_t pc_out;
    uint32_t next_pc_out;
    //...
    bool jump_out;
    bool branch_out;
    bool is_alu_out;
    bool load_out;
    bool store_out;
    char load_store_size_out;
    bool load_signed_out;
} id_intf_t;


#endif /* Interfaces_hpp */
