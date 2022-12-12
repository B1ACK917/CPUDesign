# Modern CPU Design Lab2

<p align=right>2022214053 冯大纬</p>

## CModel

### Control Signals

To connect the frontend, I set three parts of signals:

These signals follows the spec of HeHeCore, which locate at `spec\HeHecore.md`.

PC Generator Signals, connect to PCGen:

```c++
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
```

Instruction Fetch Signals, connect to FU:

```c++
typedef struct {
    bool valid;
    bool rst;
    uint32_t pc_in;
    uint32_t instruction_out;
    BUS* bus_ctrl;
} if_intf_t;
```

Instruction Decode Signals, connect to Decoder:

```c++
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
```

Although I set signals just as the HeHeCore, only part of them are used currently.(Others are used in backend or pipeline design)

### RAM

Test RAM, load the hex file to ram.

Part of the hex file:

<img src="./asset/image-20221210185216415.png" alt="image-20221210185216415" style="zoom:33%;" />

Load the hex to RAM:

<img src="./asset/image-20221211211536010.png" alt="image-20221211211536010" style="zoom:50%;" />

### PC Generator

Currently only generate the `pc+4`, but signals from BTB or other unit are already connected, will be used later.

```c++
RunCode PCGenarator::update() {
    //this->pc_gen_intf points to the signals connected to PCGenerator.
    this->pc_gen_intf->pc_out=this->pc_gen_intf->prev_pc+4;
    return Success;
}
```

### Fetch Unit

Currently use the `if_intf->valid`signal to check if need to fetch, use the bus to read instruction block from RAM.

```c++
RunCode FU::update() {
    if(if_intf->valid) {
        uint32_t instruction;
        auto pc_=if_intf->pc_in;
        auto bus_=if_intf->bus_ctrl;
        auto code=bus_->readWord(pc_,&instruction);
        if_intf->instruction_out=instruction;
        return code;
    }
    return Success;
}
```

Test Fetch Unit:

<img src="./asset/image-20221211211452690.png" alt="image-20221211211452690" style="zoom:50%;" />

Strictly same as the assemble file:

<img src="./asset/image-20221212110933954.png" alt="image-20221212110933954" style="zoom:50%;" />

### Decoder

Although quite a lot of signals are connected to decoder, currently only `pc_in, instruction_in`and output signals are used.

```c++
RunCode Decoder::update() {
    StaticInsn instr(id_intf->instruction_in);
    switch (instr.opcode()) {
        case OpcodeLoadFp:
            ...
            break;
            
        default:
            break;
    }
    return Success;
}
```

Test decode result:

<img src="./asset/image-20221212125310732.png" alt="image-20221212125310732" style="zoom:50%;" />

Strictly same as the assemble file:

<img src="./asset/image-20221212125423828.png" alt="image-20221212125423828" style="zoom:50%;" />

More clearly comparison:

![image-20221212161829768](./asset/image-20221212161829768.png)
