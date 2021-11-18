#-*-mode:makefile-gmake;indent-tabs-mode:t;tab-width:8;coding:utf-8-*-┐
#───vi: set et ft=make ts=8 tw=8 fenc=utf-8 :vi───────────────────────┘

PKGS += THIRD_PARTY_LUAJIT

THIRD_PARTY_LUAJIT_FILES := $(wildcard third_party/luajit/src/*)
THIRD_PARTY_LUAJIT_SRCS_C = $(filter-out %ljamalg.c,$(filter %.c,$(THIRD_PARTY_LUAJIT_FILES)))
THIRD_PARTY_LUAJIT_SRCS_S = $(filter %.S,$(THIRD_PARTY_LUAJIT_FILES))
THIRD_PARTY_LUAJIT_HDRS = $(filter %.h,$(THIRD_PARTY_LUAJIT_FILES))
THIRD_PARTY_LUAJIT_BINS = $(THIRD_PARTY_LUAJIT_COMS) $(THIRD_PARTY_LUAJIT_COMS:%=%.dbg)
THIRD_PARTY_LUAJIT = $(THIRD_PARTY_LUAJIT_DEPS) $(THIRD_PARTY_LUAJIT_A)
THIRD_PARTY_LUAJIT_A = o/$(MODE)/third_party/luajit/luajit.a

THIRD_PARTY_LUAJIT_OBJS_C =					\
	$(THIRD_PARTY_LUAJIT_SRCS_C:%.c=o/$(MODE)/%.o)

THIRD_PARTY_LUAJIT_OBJS_S =					\
	$(THIRD_PARTY_LUAJIT_SRCS_S:%.S=o/$(MODE)/%.o)

THIRD_PARTY_LUAJIT_OBJS =					\
	$(THIRD_PARTY_LUAJIT_OBJS_C)			\
	$(THIRD_PARTY_LUAJIT_OBJS_S)

THIRD_PARTY_LUAJIT_COMS =					\
	o/$(MODE)/third_party/luajit/luajit.com

# THIRD_PARTY_LUAJIT_CHECKS =				\
#	$(THIRD_PARTY_LUAJIT_A).pkg			\
#	$(THIRD_PARTY_LUAJIT_HDRS:%=o/$(MODE)/%.ok)

THIRD_PARTY_LUAJIT_DIRECTDEPS =				\
	LIBC_CALLS					\
	LIBC_FMT					\
	LIBC_INTRIN					\
	LIBC_MEM					\
	LIBC_NEXGEN32E					\
	LIBC_RUNTIME					\
	LIBC_STDIO					\
	LIBC_STR					\
	LIBC_SYSV					\
	LIBC_TIME					\
	LIBC_X						\
	LIBC_TINYMATH					\
	LIBC_UNICODE					\
	THIRD_PARTY_LINENOISE				\
	THIRD_PARTY_GDTOA

THIRD_PARTY_LUAJIT_DEPS :=					\
	$(call uniq,$(foreach x,$(THIRD_PARTY_LUAJIT_DIRECTDEPS),$($(x))))

$(THIRD_PARTY_LUAJIT_A):					\
		third_party/luajit/			\
		$(THIRD_PARTY_LUAJIT_A).pkg		\
		$(filter-out %luajit.o,$(THIRD_PARTY_LUAJIT_OBJS))

$(THIRD_PARTY_LUAJIT_A).pkg:				\
		$(THIRD_PARTY_LUAJIT_OBJS)			\
		$(foreach x,$(THIRD_PARTY_LUAJIT_DIRECTDEPS),$($(x)_A).pkg)

o/$(MODE)/third_party/luajit/luajit.com.dbg:			\
		$(THIRD_PARTY_LUAJIT_DEPS)			\
		$(THIRD_PARTY_LUAJIT_A)			\
		$(THIRD_PARTY_LUAJIT_A).pkg		\
		o/$(MODE)/third_party/luajit/src/luajit.o	\
		$(CRT)					\
		$(APE)
	@$(APELINK)

o/$(MODE)/third_party/luajit/src/lj_load.o\
o/$(MODE)/third_party/luajit/src/lib_package.o\
o/$(MODE)/third_party/luajit/src/lib_string.o\
o/$(MODE)/third_party/luajit/src/lib_aux.o:	\
		OVERRIDE_CFLAGS +=			\
			-DSTACK_FRAME_UNLIMITED

$(THIRD_PARTY_LUAJIT_OBJS_C):			\
		OVERRIDE_CFLAGS +=				\
			-DLUAJIT_ENABLE_LUA52COMPAT	\
			-DLUAJIT_NO_UNWIND			\
			-DLUAJIT_ENABLE_GC64		\
			-DLUAJIT_USE_SYSMALLOC		\
			-D_FILE_OFFSET_BITS=64		\
			-D_LARGEFILE_SOURCE			\
			-U_FORTIFY_SOURCE			\
			-DLUA_MULTILIB=\"lib\"		\
			-isystem libc/isystem		\
			-Ithird_party/luajit/src		\
			-Ithird_party/luajit/src/host	\
			-fno-stack-protector			\
			-ffunction-sections				\
			-fdata-sections

$(THIRD_PARTY_LUAJIT_OBJS_S):			\
		OVERRIDE_CFLAGS +=				\
			-DLUAJIT_ENABLE_LUA52COMPAT	\
			-DLUAJIT_NO_UNWIND			\
			-DLUAJIT_ENABLE_GC64		\
			-DLUAJIT_USE_SYSMALLOC		\
			-D_FILE_OFFSET_BITS=64		\
			-D_LARGEFILE_SOURCE			\
			-U_FORTIFY_SOURCE			\
			-DLUA_MULTILIB=\"lib\"		\
			-fno-stack-protector			\
			-isystem libc/isystem		\
			-Ithird_party/luajit/src		\
			-Ithird_party/luajit/src/host


.PHONY: o/$(MODE)/third_party/luajit
o/$(MODE)/third_party/luajit:				\
		$(THIRD_PARTY_LUAJIT_BINS)			\
		$(THIRD_PARTY_LUAJIT_CHECKS)
