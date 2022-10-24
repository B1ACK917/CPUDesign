RTLPATH = ../rtl/lab_1/src \
       ../rtl/lab_1/src/cache \
			 ../rtl/lab_1/src/cache/cacheblock \
			 ../rtl/lab_1/src/core_empty \
			 ../rtl/lab_1/src/core_empty/lsu \
			 ../rtl/lab_1/src/core_empty/pipeline \
			 ../rtl/lab_1/src/core_empty/units

RTLFILE += $(foreach p,$(RTLPATH),$(wildcard $(p)/*.v))
RTLFILE += $(foreach p,$(RTLPATH),$(wildcard $(p)/*.vh))

VCSFLAG = -full64 +v2k -kdb -debug_access+all -sverilog +vcs+lic+wait

compile:
	vcs $(VCSFLAG) -top tb.v $(RTLFILE)

clean:
	rm -rf $(filter-out $(wildcard *.v) makefile,$(wildcard *))

tt:
	@echo $(RTLPATH)
	@echo $(RTLFILE)