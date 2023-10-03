#-*-mode:makefile-gmake;indent-tabs-mode:t;tab-width:8;coding:utf-8-*-┐
#───vi: set et ft=make ts=8 tw=8 fenc=utf-8 :vi───────────────────────┘

PKGS += THIRD_PARTY_LUAJIT

# need minilua and buildvm to generate files
THIRD_PARTY_LUAJIT_MINILUA_C = \
	third_party/luajit/src/host/minilua.c
THIRD_PARTY_LUAJIT_MINILUA_O = \
	$(THIRD_PARTY_LUAJIT_MINILUA_C:%.c=o/$(MODE)/%.o)
THIRD_PARTY_LUAJIT_MINILUA = \
	o/$(MODE)/third_party/luajit/minilua.com

# this is a generated file
THIRD_PARTY_LUAJIT_BUILDVM_ARCH_H = \
	o/$(MODE)/third_party/luajit/src/host/buildvm_arch.h
THIRD_PARTY_LUAJIT_BUILDVM_SRCS = \
	$(filter-out %minilua.c,$(wildcard third_party/luajit/src/host/*.c))
THIRD_PARTY_LUAJIT_BUILDVM_OBJS = \
	$(THIRD_PARTY_LUAJIT_BUILDVM_SRCS:%.c=o/$(MODE)/%.o)
THIRD_PARTY_LUAJIT_BUILDVM =	\
	o/$(MODE)/third_party/luajit/buildvm.com

THIRD_PARTY_LUAJIT_FILES := $(wildcard third_party/luajit/src/*)

# these are generated files
THIRD_PARTY_LUAJIT_DEFS_H = \
	o/$(MODE)/third_party/luajit/src/lj_bcdef.h\
	o/$(MODE)/third_party/luajit/src/lj_ffdef.h\
	o/$(MODE)/third_party/luajit/src/lj_folddef.h\
	o/$(MODE)/third_party/luajit/src/lj_libdef.h\
	o/$(MODE)/third_party/luajit/src/lj_recdef.h

# this is a generated file
THIRD_PARTY_LUAJIT_VM_S = o/$(MODE)/third_party/luajit/src/lj_vm.S

THIRD_PARTY_LUAJIT_SRCS_C = $(filter-out %ljamalg.c,$(filter %.c,$(THIRD_PARTY_LUAJIT_FILES)))
THIRD_PARTY_LUAJIT_HDRS = \
	$(filter %.h,$(THIRD_PARTY_LUAJIT_FILES)) \
	$(THIRD_PARTY_LUAJIT_DEFS_H)
THIRD_PARTY_LUAJIT_BINS = $(THIRD_PARTY_LUAJIT_COMS) $(THIRD_PARTY_LUAJIT_COMS:%=%.dbg)
THIRD_PARTY_LUAJIT = $(THIRD_PARTY_LUAJIT_DEPS) $(THIRD_PARTY_LUAJIT_A)
THIRD_PARTY_LUAJIT_A = o/$(MODE)/third_party/luajit/luajit.a

THIRD_PARTY_LUAJIT_LJLIB_C = \
	third_party/luajit/src/lib_base.c	\
	third_party/luajit/src/lib_math.c	\
	third_party/luajit/src/lib_bit.c	\
	third_party/luajit/src/lib_string.c	\
	third_party/luajit/src/lib_table.c	\
	third_party/luajit/src/lib_io.c	\
	third_party/luajit/src/lib_os.c	\
	third_party/luajit/src/lib_package.c	\
	third_party/luajit/src/lib_debug.c	\
	third_party/luajit/src/lib_jit.c	\
	third_party/luajit/src/lib_ffi.c

THIRD_PARTY_LUAJIT_OBJS_C =					\
	$(THIRD_PARTY_LUAJIT_SRCS_C:%.c=o/$(MODE)/%.o)

THIRD_PARTY_LUAJIT_OBJS_S =					\
	$(THIRD_PARTY_LUAJIT_VM_S:%.S=%.o)

THIRD_PARTY_LUAJIT_OBJS =					\
	$(THIRD_PARTY_LUAJIT_OBJS_C)			\
	$(THIRD_PARTY_LUAJIT_OBJS_S)

THIRD_PARTY_LUAJIT_COMS =					\
	$(THIRD_PARTY_LUAJIT_MINILUA)			\
	$(THIRD_PARTY_LUAJIT_BUILDVM)			\
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
	LIBC_PROC					\
	LIBC_RUNTIME					\
	LIBC_STDIO					\
	LIBC_STR					\
	LIBC_SYSV					\
	LIBC_THREAD					\
	LIBC_TIME					\
	LIBC_X						\
	LIBC_TINYMATH					\
	THIRD_PARTY_LINENOISE				\
	THIRD_PARTY_GDTOA

THIRD_PARTY_LUAJIT_DEPS :=					\
	$(call uniq,$(foreach x,$(THIRD_PARTY_LUAJIT_DIRECTDEPS),$($(x))))

o/$(MODE)/third_party/luajit/minilua.com.dbg:			\
		$(THIRD_PARTY_LUAJIT_DEPS)			\
		$(THIRD_PARTY_LUAJIT_MINILUA_O)		\
		$(CRT)					\
		$(APE)
	@$(APELINK)

$(THIRD_PARTY_LUAJIT_MINILUA_O):\
		OVERRIDE_CFLAGS +=				\
			-DLUAJIT_ENABLE_LUA52COMPAT	\
			-DLUAJIT_ENABLE_GC64		\
			-DLUAJIT_USE_SYSMALLOC		\
			-DLUAJIT_TARGET_ARCH=LUAJIT_ARCH_x64 	\
			-DLJ_ARCH_HASFPU=1			\
			-DLJ_ABI_SOFTFP=0			\
			-DSTACK_FRAME_UNLIMITED		\
			-isystem libc/isystem		\
			-Ithird_party/luajit/src		\
			-Ithird_party/luajit/src/host	\
			-Io/$(MODE)/third_party/luajit/src/host	\
			-fno-stack-protector			\
			-ffunction-sections				\
			-fdata-sections

$(THIRD_PARTY_LUAJIT_BUILDVM_ARCH_H): \
		$(THIRD_PARTY_LUAJIT_MINILUA) \
		third_party/luajit/dynasm/dynasm.lua
	$(THIRD_PARTY_LUAJIT_MINILUA) \
		third_party/luajit/dynasm/dynasm.lua \
		-D ENDIAN_LE -D P64 -D JIT -D FFI \
		-D FPU -D HFABI -D VER= \
		-o $@ \
		third_party/luajit/src/vm_x64.dasc

o/$(MODE)/third_party/luajit/buildvm.com.dbg:\
		$(THIRD_PARTY_LUAJIT_DEPS)			\
		$(THIRD_PARTY_LUAJIT_BUILDVM_OBJS)	\
		$(CRT)					\
		$(APE)
	@$(APELINK)

o/$(MODE)/third_party/luajit/src/host/buildvm.o:\
		$(THIRD_PARTY_LUAJIT_BUILDVM_ARCH_H)

$(THIRD_PARTY_LUAJIT_BUILDVM_OBJS):\
		OVERRIDE_CFLAGS +=				\
			-DLUAJIT_OS=LUAJIT_OS_POSIX	\
			-DLUAJIT_ENABLE_LUA52COMPAT	\
			-DLUAJIT_ENABLE_GC64		\
			-DLUAJIT_USE_SYSMALLOC		\
			-DLUAJIT_TARGET_ARCH=LUAJIT_ARCH_x64 	\
			-DLJ_ARCH_HASFPU=1			\
			-DLJ_ABI_SOFTFP=0			\
			-DSTACK_FRAME_UNLIMITED		\
			-isystem libc/isystem		\
			-Ithird_party/luajit/src		\
			-Ithird_party/luajit/src/host		\
			-Io/$(MODE)/third_party/luajit/src/host		\
			-fno-stack-protector			\
			-ffunction-sections				\
			-fdata-sections

$(THIRD_PARTY_LUAJIT_VM_S): \
		$(THIRD_PARTY_LUAJIT_BUILDVM)
	$(THIRD_PARTY_LUAJIT_BUILDVM) -m elfasm -o $(THIRD_PARTY_LUAJIT_VM_S)

o/$(MODE)/third_party/luajit/src/lj_ffdef.h: \
		$(THIRD_PARTY_LUAJIT_BUILDVM)
	$(THIRD_PARTY_LUAJIT_BUILDVM) -m ffdef -o $@ $(THIRD_PARTY_LUAJIT_LJLIB_C)

o/$(MODE)/third_party/luajit/src/lj_bcdef.h: \
		$(THIRD_PARTY_LUAJIT_BUILDVM)
	$(THIRD_PARTY_LUAJIT_BUILDVM) -m bcdef -o $@ $(THIRD_PARTY_LUAJIT_LJLIB_C)

o/$(MODE)/third_party/luajit/src/lj_recdef.h: \
		$(THIRD_PARTY_LUAJIT_BUILDVM)
	$(THIRD_PARTY_LUAJIT_BUILDVM) -m recdef -o $@ $(THIRD_PARTY_LUAJIT_LJLIB_C)

o/$(MODE)/third_party/luajit/src/lj_folddef.h: \
		$(THIRD_PARTY_LUAJIT_BUILDVM)
	$(THIRD_PARTY_LUAJIT_BUILDVM) -m folddef -o $@ $(THIRD_PARTY_LUAJIT_LJLIB_C)

o/$(MODE)/third_party/luajit/src/lj_libdef.h: \
		$(THIRD_PARTY_LUAJIT_BUILDVM)
	$(THIRD_PARTY_LUAJIT_BUILDVM) -m libdef -o $@ $(THIRD_PARTY_LUAJIT_LJLIB_C)

$(THIRD_PARTY_LUAJIT_A):					\
		third_party/luajit/			\
		$(THIRD_PARTY_LUAJIT_A).pkg		\
		$(filter-out %luajit.o,$(THIRD_PARTY_LUAJIT_OBJS))

$(THIRD_PARTY_LUAJIT_A).pkg:				\
		$(THIRD_PARTY_LUAJIT_MINILUA)		\
		$(THIRD_PARTY_LUAJIT_BUILDVM)		\
		$(THIRD_PARTY_LUAJIT_DEFS_H)		\
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

o/$(MODE)/third_party/luajit/src/lib_base.o	\
o/$(MODE)/third_party/luajit/src/lib_debug.o	\
o/$(MODE)/third_party/luajit/src/lib_ffi.o	\
o/$(MODE)/third_party/luajit/src/lib_io.o	\
o/$(MODE)/third_party/luajit/src/lib_jit.o	\
o/$(MODE)/third_party/luajit/src/lib_math.o	\
o/$(MODE)/third_party/luajit/src/lib_os.o	\
o/$(MODE)/third_party/luajit/src/lib_bit.o	\
o/$(MODE)/third_party/luajit/src/lib_table.o	\
o/$(MODE)/third_party/luajit/src/lib_string.o	\
o/$(MODE)/third_party/luajit/src/lj_crecord.o	\
o/$(MODE)/third_party/luajit/src/lj_dispatch.o	\
o/$(MODE)/third_party/luajit/src/lj_err.o	\
o/$(MODE)/third_party/luajit/src/lj_ffrecord.o	\
o/$(MODE)/third_party/luajit/src/lj_opt_fold.o \
o/$(MODE)/third_party/luajit/src/lj_record.o:	\
	$(THIRD_PARTY_LUAJIT_DEFS_H)

$(THIRD_PARTY_LUAJIT_OBJS_C):			\
		OVERRIDE_CFLAGS +=				\
			-DLUAJIT_OS=LUAJIT_OS_POSIX	\
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
			-Io/$(MODE)/third_party/luajit/src \
			-fno-stack-protector			\
			-ffunction-sections				\
			-fdata-sections

$(THIRD_PARTY_LUAJIT_OBJS_S):			\
		OVERRIDE_CFLAGS +=				\
			-DLUAJIT_OS=LUAJIT_OS_POSIX	\
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
			-Io/$(MODE)/third_party/luajit/src \
			-Ithird_party/luajit/src


.PHONY: o/$(MODE)/third_party/luajit
o/$(MODE)/third_party/luajit:				\
		$(THIRD_PARTY_LUAJIT_BINS)
