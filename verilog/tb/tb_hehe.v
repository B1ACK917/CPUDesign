`timescale  1ns / 1ps

module tb_hehe;

// hehe Parameters
parameter PERIOD            = 10;
parameter XLEN              = 64;
parameter VIRTUAL_ADDR_LEN  = 32;
parameter WB_DATA_LEN       = 32;

initial begin
    `ifdef dumpon
        $vcdpluson();
        $fsdbDumpvars("+all");
        $fsdbDumpon;
    `endif
end

// hehe Inputs
reg   clk                                   ;
reg   reset                                 ;
reg   meip                                  ;
wire   [31:0]  m2_wbd_dat_i                 ;
wire   m2_wbd_ack_i                         ;
wire   m2_wbd_lack_i                        ;
wire   m2_wbd_err_i                         ;
wire   [31:0]  m3_wbd_dat_i                 ;
wire   m3_wbd_ack_i                         ;
wire   m3_wbd_lack_i                        ;
wire   m3_wbd_err_i                         ;

// hehe Outputs
wire  [31:0]  m2_wbd_dat_o                 ;
wire  [31:0]  m2_wbd_adr_o                 ;
wire  [3:0]  m2_wbd_sel_o                  ;
wire  [9:0]  m2_wbd_bl_o                   ;
wire  m2_wbd_bry_o                         ;
wire  m2_wbd_we_o                          ;
wire  m2_wbd_cyc_o                         ;
wire  m2_wbd_stb_o                         ;
wire  [31:0]  m3_wbd_adr_o                 ;
wire  [3:0]  m3_wbd_sel_o                  ;
wire  [9:0]  m3_wbd_bl_o                   ;
wire  m3_wbd_bry_o                         ;
wire  m3_wbd_we_o                          ;
wire  m3_wbd_cyc_o                         ;
wire  m3_wbd_stb_o                         ;

//slave
wire [31:0] s1_wdat;
wire [31:0] s1_adr;
wire [3:0] s1_sel;
wire s1_we;
wire s1_cyc;
wire s1_stb;
wire [31:0] s1_rdat;
wire s1_ack;


initial
begin
    forever #(PERIOD/2)  clk=~clk;
end

initial begin
    clk = 0;
    reset = 1;
    repeat (600) @(posedge clk);
    reset = 0;
end

hehe #(
    .XLEN             ( XLEN             ),
    .VIRTUAL_ADDR_LEN ( VIRTUAL_ADDR_LEN ),
    .WB_DATA_LEN      ( WB_DATA_LEN      ))
 u_hehe (
    .clk                     ( clk                   ),
    .reset                   ( reset                 ),
    .meip                    ( meip                  ),
    .m2_wbd_dat_i            ( m2_wbd_dat_i   [31:0] ),
    .m2_wbd_ack_i            ( m2_wbd_ack_i          ),
    .m2_wbd_lack_i           ( m2_wbd_lack_i         ),
    .m2_wbd_err_i            ( m2_wbd_err_i          ),
    .m3_wbd_dat_i            ( m3_wbd_dat_i   [31:0] ),
    .m3_wbd_ack_i            ( m3_wbd_ack_i          ),
    .m3_wbd_lack_i           ( m3_wbd_lack_i         ),
    .m3_wbd_err_i            ( m3_wbd_err_i          ),

    .m2_wbd_dat_o            ( m2_wbd_dat_o   [31:0] ),
    .m2_wbd_adr_o            ( m2_wbd_adr_o   [31:0] ),
    .m2_wbd_sel_o            ( m2_wbd_sel_o   [3:0]  ),
    .m2_wbd_bl_o             ( m2_wbd_bl_o    [9:0]  ),
    .m2_wbd_bry_o            ( m2_wbd_bry_o          ),
    .m2_wbd_we_o             ( m2_wbd_we_o           ),
    .m2_wbd_cyc_o            ( m2_wbd_cyc_o          ),
    .m2_wbd_stb_o            ( m2_wbd_stb_o          ),
    .m3_wbd_adr_o            ( m3_wbd_adr_o   [31:0] ),
    .m3_wbd_sel_o            ( m3_wbd_sel_o   [3:0]  ),
    .m3_wbd_bl_o             ( m3_wbd_bl_o    [9:0]  ),
    .m3_wbd_bry_o            ( m3_wbd_bry_o          ),
    .m3_wbd_we_o             ( m3_wbd_we_o           ),
    .m3_wbd_cyc_o            ( m3_wbd_cyc_o          ),
    .m3_wbd_stb_o            ( m3_wbd_stb_o          )
);

wire valid = u_hehe.dcache_req_valid;
wire ready = u_hehe.dcache_req_ready;
wire [31:0] addr = u_hehe.dcache_req_addr;
wire we = u_hehe.dcache_opcode;
wire [31:0] data = u_hehe.dcache_st_data[31:0];

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
    if(reset) begin
        mem_ack <= 32'b0;
    end else begin
        mem_ack <= next_ack;
    end
end

dpram64 #(
    .SIZE(1<<16), // byte
    .mem_clear(1'b1),
    .memfile("isa/hex/rv64ui-p-add.hex")
) magicmemory(
    .clk(clk),
    .we(s1_we),
    .din(s1_wdat),
    .waddr(s1_adr),
    .raddr(s1_adr),
    .dout(s1_rdat)
);

wb_interconnect wb_interconnect_u
(
        .clk_i (clk),
        .rst_n (~reset),

         // Master 0 Interface icache
         .m0_wbd_dat_i (m2_wbd_dat_o),
         .m0_wbd_adr_i (m2_wbd_adr_o-32'h80000000),  //fix
         .m0_wbd_sel_i (m2_wbd_sel_o),
         .m0_wbd_we_i (m2_wbd_we_o),
         .m0_wbd_cyc_i (m2_wbd_cyc_o),
         .m0_wbd_stb_i (m2_wbd_stb_o),
         .m0_wbd_dat_o (m2_wbd_dat_i),
         .m0_wbd_ack_o (m2_wbd_ack_i),
         .m0_wbd_lack_o (),
         .m0_wbd_err_o (),
         
         // Master 1 Interface dcache
         .m1_wbd_dat_i (),
         .m1_wbd_adr_i (m3_wbd_adr_o-32'h80000000),
         .m1_wbd_sel_i (m3_wbd_sel_o),
         .m1_wbd_bl_i (),
         .m1_wbd_bry_i (),
         .m1_wbd_we_i (m3_wbd_we_o),
         .m1_wbd_cyc_i (m3_wbd_cyc_o),
         .m1_wbd_stb_i (m3_wbd_stb_o),
         .m1_wbd_dat_o (m3_wbd_dat_i),
         .m1_wbd_ack_o (m3_wbd_ack_i),
         .m1_wbd_lack_o (),
         .m1_wbd_err_o (),

         // Slave 0 Interface
         .s_wbd_dat_i (s1_rdat),
         .s_wbd_ack_i (s1_ack),
         .s_wbd_lack_i (),
         .s_wbd_dat_o (s1_wdat),
         .s_wbd_adr_o (s1_adr),
         .s_wbd_sel_o (s1_sel),
         .s_wbd_bl_o (),
         .s_wbd_bry_o (),
         .s_wbd_we_o (s1_we),
         .s_wbd_cyc_o (s1_cyc),
         .s_wbd_stb_o (s1_stb)
);


endmodule