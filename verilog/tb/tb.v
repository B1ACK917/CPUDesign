`timescale 1ns/1ps
`default_nettype  wire

module hehe_tb;

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
end 

endmodule