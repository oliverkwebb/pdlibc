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
wrap(read)
wrap(open)
wrap(close)
wrap(time)
wrap(lseek)
wrap(getpid) // raise
wrap(rename)


.global exit
exit:
  call ___end_libc
  mov edi, eax
  mov eax, __NR_exit
  jmp _syscall
