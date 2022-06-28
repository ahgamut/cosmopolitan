#-*-mode:makefile-gmake;indent-tabs-mode:t;tab-width:8;coding:utf-8-*-┐
#───vi: set et ft=make ts=8 tw=8 fenc=utf-8 :vi───────────────────────┘

PKGS += THIRD_PARTY_DABBAJSON

THIRD_PARTY_DABBAJSON_ARTIFACTS += THIRD_PARTY_DABBAJSON_A

THIRD_PARTY_DABBAJSON = \
	$(THIRD_PARTY_DABBAJSON_DEPS) \
	$(THIRD_PARTY_DABBAJSON_A)

THIRD_PARTY_DABBAJSON_A = \
	o/$(MODE)/third_party/dabbajson/dabbajson.a

THIRD_PARTY_DABBAJSON_A_FILES := $(wildcard third_party/dabbajson/*)
THIRD_PARTY_DABBAJSON_A_SRCS_C = \
	third_party/dabbajson/dabbajson.c \
	third_party/dabbajson/write.c

THIRD_PARTY_DABBAJSON_A_HDRS = $(filter %.h,$(THIRD_PARTY_DABBAJSON_A_FILES))

THIRD_PARTY_DABBAJSON_A_OBJS =						\
	$(THIRD_PARTY_DABBAJSON_A_SRCS_C:%.c=o/$(MODE)/%.o)

THIRD_PARTY_DABBAJSON_A_CHECKS =						\
	$(THIRD_PARTY_DABBAJSON_A).pkg					\
	$(THIRD_PARTY_DABBAJSON_A_HDRS:%=o/$(MODE)/%.ok)

THIRD_PARTY_DABBAJSON_COMS = o/$(MODE)/third_party/dabbajson/runner.com
THIRD_PARTY_DABBAJSON_BINS = \
		$(THIRD_PARTY_DABBAJSON_COMS) \
		$(THIRD_PARTY_DABBAJSON_COMS:%=%.dbg)
THIRD_PARTY_DABBAJSON_RUNS = \
		$(THIRD_PARTY_DABBAJSON_COMS:%=%.runs)

THIRD_PARTY_DABBAJSON_A_DIRECTDEPS =					\
	LIBC_INTRIN								\
	LIBC_NEXGEN32E								\
	LIBC_RUNTIME								\
	LIBC_MEM								\
	LIBC_LOG								\
	LIBC_STDIO								\
	LIBC_FMT								\
	LIBC_SYSV								\
	LIBC_STR								\
	LIBC_STUBS

THIRD_PARTY_DABBAJSON_A_DEPS :=						\
	$(call uniq,$(foreach x,$(THIRD_PARTY_DABBAJSON_A_DIRECTDEPS),$($(x))))

$(THIRD_PARTY_DABBAJSON_A):						\
		third_party/dabbajson/					\
		$(THIRD_PARTY_DABBAJSON_A).pkg				\
		$(THIRD_PARTY_DABBAJSON_A_OBJS)

$(THIRD_PARTY_DABBAJSON_A).pkg:						\
		$(THIRD_PARTY_DABBAJSON_A_OBJS)				\
		$(foreach x,$(THIRD_PARTY_DABBAJSON_A_DIRECTDEPS),$($(x)_A).pkg)

$(THIRD_PARTY_DABBAJSON_A_OBJS):						\
		OVERRIDE_CXXFLAGS +=						\
			-ffunction-sections					\
			-fdata-sections

o/$(MODE)/third_party/dabbajson/runner.com.dbg:	\
		$(THIRD_PARTY_DABBAJSON_A_DEPS)				\
		$(THIRD_PARTY_DABBAJSON_A)				\
		o/$(MODE)/third_party/dabbajson/runner.o			\
		$(CRT)								\
		$(APE_NO_MODIFY_SELF)
	@$(APELINK)

o/$(MODE)/third_party/dabbajson/runner.com.runs: \
	o/$(MODE)/third_party/dabbajson/runner.com
	@$(COMPILE) -ACHECK -tT$@ $<

THIRD_PARTY_DABBAJSON_LIBS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)))
THIRD_PARTY_DABBAJSON_SRCS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)_SRCS))
THIRD_PARTY_DABBAJSON_HDRS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)_HDRS))
THIRD_PARTY_DABBAJSON_CHECKS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)_CHECKS))
THIRD_PARTY_DABBAJSON_OBJS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)_OBJS))

.PHONY: o/$(MODE)/third_party/dabbajson
o/$(MODE)/third_party/dabbajson:					\
		$(THIRD_PARTY_DABBAJSON_RUNS)

