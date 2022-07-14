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
	third_party/dabbajson/element.c \
	third_party/dabbajson/read.c \
	third_party/dabbajson/bufread.c \
	third_party/dabbajson/write.c	\
	third_party/dabbajson/bufwrite.c

THIRD_PARTY_DABBAJSON_A_HDRS = $(filter %.h,$(THIRD_PARTY_DABBAJSON_A_FILES))

THIRD_PARTY_DABBAJSON_TEST_FILES := $(wildcard third_party/dabbajson/test/test-*)
THIRD_PARTY_DABBAJSON_TEST_SRCS_C = $(filter %.c,$(THIRD_PARTY_DABBAJSON_TEST_FILES))

THIRD_PARTY_DABBAJSON_SAMPLES_PASS := $(wildcard third_party/dabbajson/test/pass/*)
THIRD_PARTY_DABBAJSON_SAMPLES_EITHER := $(wildcard third_party/dabbajson/test/either/*)
THIRD_PARTY_DABBAJSON_SAMPLES_FAIL := $(wildcard third_party/dabbajson/test/fail/*)
THIRD_PARTY_DABBAJSON_SAMPLES = \
	$(THIRD_PARTY_DABBAJSON_SAMPLES_PASS) \
	$(THIRD_PARTY_DABBAJSON_SAMPLES_EITHER) \
	$(THIRD_PARTY_DABBAJSON_SAMPLES_FAIL)

THIRD_PARTY_DABBAJSON_SAMPLES_OBJS = \
	$(THIRD_PARTY_DABBAJSON_A_SAMPLES:%=o/$(MODE)/%.zip.o)

THIRD_PARTY_DABBAJSON_A_OBJS =						\
	$(THIRD_PARTY_DABBAJSON_A_SRCS_C:%.c=o/$(MODE)/%.o)

THIRD_PARTY_DABBAJSON_A_CHECKS =						\
	$(THIRD_PARTY_DABBAJSON_A).pkg					\
	$(THIRD_PARTY_DABBAJSON_A_HDRS:%=o/$(MODE)/%.ok)

THIRD_PARTY_DABBAJSON_COMS = \
	$(THIRD_PARTY_DABBAJSON_TEST_SRCS_C:%.c=o/$(MODE)/%.com)
THIRD_PARTY_DABBAJSON_BINS = \
		$(THIRD_PARTY_DABBAJSON_COMS) \
		$(THIRD_PARTY_DABBAJSON_COMS:%=%.dbg)
THIRD_PARTY_DABBAJSON_RUNS = \
		$(THIRD_PARTY_DABBAJSON_SAMPLES:%=o/$(MODE)/%.runs)

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
	LIBC_UNICODE							\
	LIBC_STUBS								\
	THIRD_PARTY_GDTOA

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

o/$(MODE)/third_party/dabbajson/test/%.com.dbg:	\
		$(THIRD_PARTY_DABBAJSON_A_DEPS)				\
		$(THIRD_PARTY_DABBAJSON_A)				\
		o/$(MODE)/third_party/dabbajson/test/helper.o			\
		o/$(MODE)/third_party/dabbajson/test/%.o				\
		$(CRT)								\
		$(APE_NO_MODIFY_SELF)
	@$(APELINK)

o/$(MODE)/third_party/dabbajson/test/pass/%.json.runs: \
	o/$(MODE)/third_party/dabbajson/test/test-passer.com	\
	third_party/dabbajson/test/pass/%.json
	@$(COMPILE) -ACHECK -tT$@ $^

o/$(MODE)/third_party/dabbajson/test/fail/%.json.runs: \
	o/$(MODE)/third_party/dabbajson/test/test-failer.com	\
	third_party/dabbajson/test/fail/%.json
	@$(COMPILE) -ACHECK -tT$@ $^

o/$(MODE)/third_party/dabbajson/test/either/%.json.runs: \
	o/$(MODE)/third_party/dabbajson/test/test-either.com	\
	third_party/dabbajson/test/either/%.json
	@$(COMPILE) -ACHECK -tT$@ $^

THIRD_PARTY_DABBAJSON_LIBS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)))
THIRD_PARTY_DABBAJSON_SRCS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)_SRCS))
THIRD_PARTY_DABBAJSON_HDRS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)_HDRS))
THIRD_PARTY_DABBAJSON_CHECKS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)_CHECKS))
THIRD_PARTY_DABBAJSON_OBJS = $(foreach x,$(THIRD_PARTY_DABBAJSON_ARTIFACTS),$($(x)_OBJS))

.PHONY: o/$(MODE)/third_party/dabbajson
o/$(MODE)/third_party/dabbajson:					\
		$(THIRD_PARTY_DABBAJSON_RUNS)

