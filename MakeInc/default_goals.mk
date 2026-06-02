#$(patsubst %.c,build/*.o,$(wildcard *.c)) :

build/%.o: %.c
	@mkdir -p build
	@printf "\e[31;44mCC $*.c\e[0m\n"
	@$(CC) -c $< $(CFLAGS) $(INC) -o $@

%.elf:
	@printf "\e[36m$(?F) -> $@\e[0m\n"
	@$(CC) $^ $(INC) $(LDFLAGS) -o $@

clean:
	rm -rf build
