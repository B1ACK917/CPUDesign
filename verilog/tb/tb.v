`timescale 1ns/1ps
`default_nettype  wire

module hehe_tb;

localparam HALF_CLK_PERIORD = 10;	
localparam AXI_ID_WIDTH = 10;
localparam VIRTUAL_ADDR_LEN = 32;
localparam DATA_WIDTH = 32;

reg clk = 0;
reg rst;

always #(HALF_CLK_PERIORD) clk = ~clk;

// string image_path;
initial begin
	if ($test$plusargs("dump")) begin
        $vcdpluson();

		//fsdb wave
        $fsdbDumpfile("./logs/waves.fsdb");
        $fsdbDumpvars(0, hehe_tb);
        $fsdbDumpvars("+struct");
        $fsdbDumpvars("+mda");
        $fsdbDumpvars("+all");
        $fsdbDumpon;
    end

    // $value$plusargs("hex=%s", image_path);
end 


wire valid = hehe_u.dcache_req_valid;
wire ready = hehe_u.dcache_req_ready;
wire [31:0] addr = hehe_u.dcache_req_addr;
wire we = hehe_u.dcache_opcode;
wire [31:0] data = hehe_u.dcache_st_data[31:0];

always @(posedge clk) begin  //exiter
    if(valid && ready && (addr == 32'h80001000) && we) begin
        if(data == 32'b1) begin
            $display("pass test");
        end else begin
            $display("fail test");
        end
        $finish;
    end
end

initial begin
    repeat (50000) @(posedge clk);
    $display("time runout, simulating terminated");
    $finish;
end

wire [31:0] m2_wdat;
wire [31:0] m2_adr;
wire [3:0] m2_sel;
wire m2_we;
wire m2_cyc;
wire m2_stb;
wire [31:0] m2_rdat;
wire m2_ack;

wire [31:0] m3_adr;
wire [3:0] m3_sel;
wire m3_we;
wire m3_cyc;
wire m3_stb;
wire [31:0] m3_rdat;
wire m3_ack;

wire [31:0] s1_wdat;
wire [31:0] s1_adr;
wire [3:0] s1_sel;
wire s1_we;
wire s1_cyc;
wire s1_stb;
wire [31:0] s1_rdat;
wire s1_ack;

initial begin
    clk = 0;
    rst = 1;
    repeat (600) @(posedge clk);
    rst = 0;
end

hehe #(
    .XLEN(64),
    .VIRTUAL_ADDR_LEN(32),
    .WB_DATA_LEN(32)
) hehe_u (
    .clk(clk),
    .reset(rst),
    .meip(1'b0),
    
    // d$ / lsu <-> Soc
    .m2_wbd_dat_o(m2_wdat), 
    .m2_wbd_adr_o(m2_adr), 
    .m2_wbd_sel_o(m2_sel),
    .m2_wbd_bl_o(),
    .m2_wbd_bry_o(),
    .m2_wbd_we_o(m2_we),
    .m2_wbd_cyc_o(m2_cyc),
    .m2_wbd_stb_o(m2_stb),
    .m2_wbd_dat_i(m2_rdat),
    .m2_wbd_ack_i(m2_ack), 
    

    // I$ <-> Soc
    .m3_wbd_adr_o(m3_adr),
    .m3_wbd_sel_o(m3_sel),
    .m3_wbd_bl_o(),
    .m3_wbd_bry_o(),
    .m3_wbd_we_o(m3_we),
    .m3_wbd_cyc_o(m3_cyc),
    .m3_wbd_stb_o(m3_stb),   
    .m3_wbd_dat_i(m3_rdat),
    .m3_wbd_ack_i(m3_ack),
    .m3_wbd_lack_i(),
    .m3_wbd_err_i()
);


reg mem_ack;
reg next_ack;

assign s1_ack = mem_ack && s1_cyc;
always @(*) begin
    next_ack = mem_ack;
    if(s1_cyc) begin
        next_ack = 1'b1;
    end else begin
        next_ack = 1'b0;
    end
end

always @(posedge clk) begin
    if(rst) begin
        mem_ack <= 32'b0;
    end else begin
        mem_ack <= next_ack;
    end
end

dpram64 #(
    .SIZE(1<<16), // byte
    .mem_clear(1'b1),
    .memfile("/work/stu/dwfeng/CPULab/CPUDesign/verilog/tb/isa/hex/add.hex")
) magicmemory(
    .clk(clk),
    .we(s1_we),
    .din(s1_wdat),
    .waddr(s1_adr),
    .raddr(s1_adr),
    .dout(s1_rdat)
);

endmodule