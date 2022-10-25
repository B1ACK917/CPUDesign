RTLPATH = ../rtl/lab_1/src \
	../rtl/lab_1/src/cache \
	../rtl/lab_1/src/cache/cacheblock \
	../rtl/lab_1/src/core_empty \
	../rtl/lab_1/src/core_empty/lsu \
	../rtl/lab_1/src/core_empty/pipeline \
	../rtl/lab_1/src/core_empty/units \
	.

RTLFILE += $(foreach p,$(RTLPATH),$(wildcard $(p)/*.v $(p)/*.sv))

VCSFLAG = -full64 +v2k -kdb -debug_access+all +define+dumpon \
	-sverilog +vcs+lic+wait +vc+list +vpi \
	-timescale=1ns/1ps -v2k_generate +incdir+../rtl/lab_1/src

# VFLAG = +vcs+lic+wait -sverilog -kdb +vc+list +vpi\
# 		+error+20 +lint=TFIPC-L +lint=IIMW-L +lint=GCWM-L +lint=CAWM-L \
# 		+lint=PCWM-L -full64 -timescale=1ns/1ps \
# 		-v2k_generate -debug_access+all +incdir+../rtl/lab_1/src

ELF2HEX = elf2hex.py
ELFPATH = isa/elf
ELFFILE += $(notdir $(foreach p,$(ELFPATH),$(wildcard $(p)/*)))
HEXFILE = $(addsuffix .hex, $(ELFFILE))

#build simv
compile:
	vcs $(VCSFLAG) $(RTLFILE) -top tb_hehe

#build hex file
hex:
	for x in $(ELFFILE); do \
	 python3 $(ELF2HEX) --bit-width 128 --infile isa/elf/$$x --outfile isa/hex/$$x.hex; \
	done

run:
	./simv 2>&1 | tee run.log

all: hex compile run

clean:
	rm -rf $(filter-out $(wildcard *.v *.sv *.py) makefile isa ,$(wildcard *))
	rm -rf isa/hex/*.hex
	rm -rf temp

#test
tt:
	@echo $(RTLPATH)
	@echo $(RTLFILE)
	@echo $(ELFFILE)
	@echo $(HEXFILE)