LIBCA=libc.a
OLIB=lib/
CRTI_LIBCA=crti_$(LIBCA)

export CC CFLAGS INCFLAGS LIBCA CRTI_LIBCA NOSTDFLAGS
CC=gcc
NOSTDFLAGS=-nostdlib -ffreestanding
SHUTUP= -Wno-pointer-arith -Wno-discarded-qualifiers
CFLAGS= -pedantic -Wall -static -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-pie -Os -fdata-sections -ffunction-sections -fno-stack-protector $(MYCFLAGS) $(SHUTUP)
INCFLAGS= -I include/ -nostdinc
CSOURCE=$(wildcard src/*.c)
ASMSOURCE=$(wildcard src/*.S)
OBJFILES= $(patsubst src/%.c, obj/%.o, $(CSOURCE)) $(patsubst src/%.S, obj/%.o, $(ASMSOURCE))

Q=@

.PHONY: all clean test

all: $(LIBCA)

$(LIBCA): $(OBJFILES)
	rm -f $(LIBCA)
	ar rs $(OLIB)$@ $^

# SPECIAL CASE: We need the syscall numbers from asm/unistd.h
obj/syscalls.o: src/syscalls.S
	$(Q)printf "CC %-20s -> $@\n" "$<"
	$(Q)$(CC) $(CFLAGS) $(NOSTDFLAGS) $< -c -o $@

obj/%.o: src/%.[cS]
	$(Q)printf "CC %-20s -> $@\n" "$<"
	$(Q)$(CC) $(CFLAGS) $(INCFLAGS) $(NOSTDFLAGS) $< -c -o $@

clean:
	rm -f $(OLIB)* obj/*.o

test: $(LIBCA)
	@./test.sh
