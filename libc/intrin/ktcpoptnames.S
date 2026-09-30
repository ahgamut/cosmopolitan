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
	.long	\e - kTcpOptnames
	.long	.L\@ - kTcpOptnames
	.rodata.str1.1
.L\@:	.string	"\s"
	.previous
	.endm

	.section .rodata
	.balign	4
	.underrun
kTcpOptnames:
	.e	TCP_NODELAY_,"NODELAY"			// bool32
	.e	TCP_CORK_,"CORK"				// bool32
	.e	TCP_QUICKACK_,"QUICKACK"			// bool32
	.e	TCP_FASTOPEN_CONNECT_,"FASTOPEN_CONNECT"	// bool32
	.e	TCP_DEFER_ACCEPT_,"DEFER_ACCEPT"		// bool32
	.e	TCP_KEEPIDLE_,"KEEPIDLE"			// int (seconds)
	.e	TCP_KEEPINTVL_,"KEEPINTVL"		// int (seconds)
	.e	TCP_FASTOPEN_,"FASTOPEN"			// int
	.e	TCP_KEEPCNT_,"KEEPCNT"			// int
	.e	TCP_MAXSEG_,"MAXSEG"			// int
	.e	TCP_SYNCNT_,"SYNCNT"			// int
	.e	TCP_NOTSENT_LOWAT_,"NOTSENT_LOWAT"	// int
	.e	TCP_WINDOW_CLAMP_,"WINDOW_CLAMP"		// int
	.e	TCP_SAVE_SYN_,"SAVE_SYN"			// int
	.e	TCP_SAVED_SYN_,"SAVED_SYN"		// buffer
	.long	MAGNUM_TERMINATOR
	.endobj	kTcpOptnames,globl,hidden
	.overrun
