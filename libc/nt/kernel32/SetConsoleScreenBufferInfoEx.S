#include "libc/nt/codegen.h"
.imp	kernel32,__imp_SetConsoleScreenBufferInfoEx,SetConsoleScreenBufferInfoEx,0

#ifdef __x86_64__
	.text.windows
SetConsoleScreenBufferInfoEx:
	push	%rbp
	mov	%rsp,%rbp
	.profilable
	mov	__imp_SetConsoleScreenBufferInfoEx(%rip),%rax
	jmp	__sysv2nt
	.endfn	SetConsoleScreenBufferInfoEx,globl
	.previous
#endif