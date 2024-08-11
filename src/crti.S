// _start.s: Bare minimum _start code
// Copyright (C) 2024 Oliver Webb
.intel_syntax noprefix

// functions: rdi, rsi, rdx, rcx, r8, r9
//  syscalls: rdi, rsi, rdx, r10, r8, r9
//                           ^^^
// return to rax
// stack grows from high addr -> low 

.global _start
_start:
  xor rbp, rbp
  xor r9, r9
  pop rdi // argc
  mov rsi, rsp // argv
  call ___runc
