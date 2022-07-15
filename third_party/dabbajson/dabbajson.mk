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
THIRD_PARTY_DABBAJSON_SAMPLES_ALL = \
	$(THIRD_PARTY_DABBAJSON_SAMPLES_PASS) \
	$(THIRD_PARTY_DABBAJSON_SAMPLES_EITHER) \
	$(THIRD_PARTY_DABBAJSON_SAMPLES_FAIL)

THIRD_PARTY_DABBAJSON_SAMPLES_NONCOMPLY = \
	third_party/dabbajson/test/either/i_number_huge_exp.json	\
	third_party/dabbajson/test/fail/n_multidigit_number_then_00.json \
	third_party/dabbajson/test/fail/n_number_-01.json	\
	third_party/dabbajson/test/fail/n_number_-2..json	\
	third_party/dabbajson/test/fail/n_number_0.e1.json	\
	third_party/dabbajson/test/fail/n_number_2.e+3.json	\
	third_party/dabbajson/test/fail/n_number_2.e-3.json	\
	third_party/dabbajson/test/fail/n_number_2.e3.json	\
	third_party/dabbajson/test/fail/n_number_neg_int_starting_with_zero.json \
	third_party/dabbajson/test/fail/n_number_neg_real_without_int_part.json \
	third_party/dabbajson/test/fail/n_number_real_without_fractional_part.json \
	third_party/dabbajson/test/fail/n_structure_null-byte-outside-string.json \
	third_party/dabbajson/test/pass/y_string_accepted_surrogate_pair.json \
	third_party/dabbajson/test/pass/y_string_accepted_surrogate_pairs.json \
	third_party/dabbajson/test/pass/y_string_escaped_control_character.json \
	third_party/dabbajson/test/pass/y_string_last_surrogates_1_and_2.json \
	third_party/dabbajson/test/pass/y_string_nonCharacterInUTF-8_U+10FFFF.json \
	third_party/dabbajson/test/pass/y_string_nonCharacterInUTF-8_U+FFFF.json \
	third_party/dabbajson/test/pass/y_string_pi.json \
	third_party/dabbajson/test/pass/y_string_reservedCharacterInUTF-8_U+1BFFF.json \
	third_party/dabbajson/test/pass/y_string_surrogates_U+1D11E_MUSICAL_SYMBOL_G_CLEF.json \
	third_party/dabbajson/test/pass/y_string_u+2028_line_sep.json \
	third_party/dabbajson/test/pass/y_string_u+2029_par_sep.json \
	third_party/dabbajson/test/pass/y_string_unicode_2.json \
	third_party/dabbajson/test/pass/y_string_unicode_U+10FFFE_nonchar.json \
	third_party/dabbajson/test/pass/y_string_unicode_U+1FFFE_nonchar.json \
	third_party/dabbajson/test/pass/y_string_utf8.json

THIRD_PARTY_DABBAJSON_SAMPLES = \
	$(filter-out $(THIRD_PARTY_DABBAJSON_SAMPLES_NONCOMPLY),$(THIRD_PARTY_DABBAJSON_SAMPLES_ALL))

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
		$(THIRD_PARTY_DABBAJSON_BINS)				\
		$(THIRD_PARTY_DABBAJSON_RUNS)

