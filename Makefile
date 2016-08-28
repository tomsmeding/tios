# Credits to @tomsmeding

BIN = prog.8xp
PROG_NAME = PROG
main_c_file = main.c

SDCC = sdcc
SDCC_FLAGS = --no-std-crt0 --code-loc 40347 --data-loc 0 --std-sdcc99 -mz80 --reserve-regs-iy --peep-return --peep-asm --opt-code-size --allow-unsafe-read

c_files = $(filter-out $(main_c_file),$(shell echo *.c **/*.c))
rel_files = $(patsubst %.c,%.rel,$(c_files))

.PHONY: all clean remake rmtempfiles

all: $(BIN) rmtempfiles

clean: rmtempfiles
	rm -f $(BIN) $(rel_files) *.asm

rmtempfiles:
	-rm {.,lib}/*.{bin,ihx,lk,lst,map,noi,rel,sym}

remake: clean all

%.8xp: %.bin
	./binpac8x.py -O $(PROG_NAME) $< $@

%.bin: %.ihx
	./hex2bin $<

crt0.rel: crt0.s
	sdasz80 -p -g -o $@ $<

%.rel: %.c
	$(SDCC) $(SDCC_FLAGS) -c -o $@ $^

%.ihx: crt0.rel $(main_c_file) $(rel_files)
	$(SDCC) $(SDCC_FLAGS) -o $@ $^
