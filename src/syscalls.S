.intel_syntax noprefix
#include <asm/unistd.h>

// functions: rdi, rsi, rdx, rcx, r8, r9
//  syscalls: rdi, rsi, rdx, r10, r8, r9
//                           ^^^
// return to rax
// stack grows from high addr -> low

.global _syscall
_syscall:
  mov r10, rcx
  syscall
  ret

#define wrap(a) \
.global a; \
a: \
  mov eax, __NR_##a; \
  jmp _syscall

wrap(write)
wrap(open)
wrap(close)
wrap(time)
wrap(lseek)
wrap(kill)
wrap(getpid) // raise
wrap(rename)
wrap(mmap)
wrap(munmap)

.global _Exit
_Exit:
  mov eax, __NR_exit
  jmp _syscall
