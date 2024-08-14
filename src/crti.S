// _start.s: Bare minimum _start code
// Copyright (C) 2024 Oliver Webb

.global _start
_start:
  xor %rbp, %rbp
  xor %r9, %r9
  pop %rdi // argc
  mov %rsp, %rsi // argv
  and $0xfffffffffffffff0, %rsp
  call ___runc
