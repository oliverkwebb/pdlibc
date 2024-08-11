LIBCA=libc.a
CRTI_LIBCA=crti_$(LIBCA)

export CC CFLAGS INCFLAGS LIBCA CRTI_LIBCA NOSTDFLAGS
CC=gcc
NOSTDFLAGS=-nostdlib -ffreestanding
CFLAGS= -pedantic -Wall -Wl,--gc-sections -static -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-pie -Os -fdata-sections -ffunction-sections -fno-stack-protector $(MYCFLAGS)
INCFLAGS= -I include/ -nostdinc
CSOURCE=$(wildcard src/*.c)
ASMSOURCE=$(wildcard src/*.S)
OBJFILES= $(patsubst src/%.c, obj/%.o, $(CSOURCE)) $(patsubst src/%.S, obj/%.o, $(ASMSOURCE))

.PHONY: all clean test withcrti

all: $(LIBCA) withcrti

$(LIBCA): $(OBJFILES)
	rm -f $(LIBCA)
	ar rs $@ $^

withcrti: $(CRTI_LIBCA)

$(CRTI_LIBCA): $(LIBCA) src/crti.S
	rm -f $(CRTI_LIBCA)
	ar rs $(CRTI_LIBCA) obj/*.o

# SPECIAL CASE: We need the syscall numbers from asm/unistd.h
obj/syscalls.o: src/syscalls.S
	$(CC) $(CFLAGS) $(NOSTDFLAGS) $< -c -o $@

obj/%.o: src/%.[cS]
	$(CC) $(CFLAGS) $(INCFLAGS) $(NOSTDFLAGS) $< -c -o $@

clean:
	rm -f $(LIBCA) $(CRTI_LIBCA) obj/*.o

test: withcrti
	@./test.sh
