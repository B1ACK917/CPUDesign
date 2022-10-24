RTLPATH = ../rtl/lab_1/src \
	../rtl/lab_1/src/cache \
	../rtl/lab_1/src/cache/cacheblock \
	../rtl/lab_1/src/core_empty \
	../rtl/lab_1/src/core_empty/lsu \
	../rtl/lab_1/src/core_empty/pipeline \
	../rtl/lab_1/src/core_empty/units \
	.

RTLFILE += $(foreach p,$(RTLPATH),$(wildcard $(p)/*.v $(p)/*.vh $(p)/*.sv))

VCSFLAG = -full64 +v2k -kdb -debug_access+all \
	-sverilog +vcs+lic+wait +incdir+../rtl/lab_1/src\
	-timescale=1ns/1ps

ELF2HEX = /work/stu/dwfeng/RISCV/elf2hex/bin/riscv64-unknown-elf-elf2hex
ELFPATH = isa/elf
ELFFILE += $(notdir $(foreach p,$(ELFPATH),$(wildcard $(p)/*)))
HEXFILE = $(addsuffix .hex, $(ELFFILE))

#build simv
compile:
	vcs $(VCSFLAG) $(RTLFILE) -top hehe_tb

#build hex file
hex:
	for x in $(ELFFILE); do \
	 $(ELF2HEX) --bit-width 32 --input isa/elf/$$x --output isa/hex/$$x.hex; \
	done

clean:
	rm -rf $(filter-out $(wildcard *.v) makefile $(wildcard *.sv) isa,$(wildcard *))
	rm -rf isa/hex/

#test
tt:
	@echo $(RTLPATH)
	@echo $(RTLFILE)
	@echo $(ELFFILE)
	@echo $(HEXFILE)
