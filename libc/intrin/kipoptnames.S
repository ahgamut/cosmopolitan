/*-*- mode:unix-assembly; indent-tabs-mode:t; tab-width:8; coding:utf-8     -*-│
│ vi: set noet ft=asm ts=8 sw=8 fenc=utf-8                                 :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2021 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/fmt/magnumstrs.internal.h"
#include "libc/macros.h"

	.macro	.e e s
	.long	\e - kIpOptnames
	.long	.L\@ - kIpOptnames
	.rodata.str1.1
.L\@:	.string	"\s"
	.previous
	.endm

	.section .rodata
	.balign	4
	.underrun
kIpOptnames:
	.e	IP_TOS_,"TOS"			// int
	.e	IP_TTL_,"TTL"			// int
	.e	IP_MTU_,"MTU"			// int
	.e	IP_HDRINCL_,"HDRINCL"		// bool32
	.e	IP_OPTIONS_,"OPTIONS"
	.e	IP_RECVTTL_,"RECVTTL"
	.e	IP_ADD_MEMBERSHIP_,"ADD_MEMBERSHIP"
	.e	IP_DROP_MEMBERSHIP_,"DROP_MEMBERSHIP"
	.e	IP_MULTICAST_IF_,"MULTICAST_IF"
	.e	IP_MULTICAST_LOOP_,"MULTICAST_LOOP"
	.e	IP_MULTICAST_TTL_,"MULTICAST_TTL"
	.e	IP_PKTINFO_,"PKTINFO"
	.e	IP_RECVTOS_,"RECVTOS"
	.long	MAGNUM_TERMINATOR
	.endobj	kIpOptnames,globl,hidden
	.overrun
