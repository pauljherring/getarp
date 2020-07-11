
.PHONY: valgrind clean scrub

WARNING_FLAGS = \
	-Waddress \
	-Wbad-function-cast \
	-Wbuiltin-macro-redefined \
	-Wcast-align \
	-Wcast-qual \
	-Wchar-subscripts \
	-Wclobbered \
	-Wcomment \
	-Wdeclaration-after-statement \
	-Wdeprecated \
	-Wdeprecated-declarations \
	-Wdisabled-optimization \
	-Wdiv-by-zero \
	-Wdouble-promotion \
	-Wempty-body \
	-Wendif-labels \
	-Wenum-compare \
	-Wfloat-equal \
	-Wformat \
	-Wformat-contains-nul \
	-Wformat-extra-args \
	-Wformat-nonliteral \
	-Wformat-security \
	-Wformat-y2k \
	-Wformat-zero-length \
	-Wfree-nonheap-object \
	-Wignored-qualifiers \
	-Wimplicit \
	-Wimplicit-function-declaration \
	-Wimplicit-int \
	-Wimport \
	-Winit-self \
	-Winline \
	-Wint-to-pointer-cast \
	-Winvalid-memory-model \
	-Winvalid-pch \
	-Wjump-misses-init \
	-Wlogical-op \
	-Wmain \
	-Wmaybe-uninitialized \
	-Wmissing-braces \
	-Wmissing-declarations \
	-Wmissing-field-initializers \
	-Wmissing-format-attribute \
	-Wmissing-include-dirs \
	-Wmissing-parameter-type \
	-Wmissing-prototypes \
	-Wmultichar \
	-Wnarrowing \
	-Wnested-externs   \
	-Wnonnull \
	-Wold-style-declaration \
	-Wold-style-definition \
	-Woverflow \
	-Woverride-init \
	-Wpacked \
	-Wparentheses \
	-Wpedantic \
	-Wpointer-arith \
	-Wpointer-sign \
	-Wpointer-to-int-cast \
	-Wpragmas \
	-Wredundant-decls \
	-Wreturn-local-addr \
	-Wreturn-type \
	-Wsequence-point \
	-Wshadow \
	-Wsign-compare \
	-Wsizeof-pointer-memaccess \
	-Wstrict-aliasing=3 \
	-Wstrict-overflow=1 \
	-Wstrict-prototypes \
	-Wsuggest-attribute=format \
	-Wsuggest-attribute=noreturn \
	-Wswitch \
	-Wswitch-default \
	-Wswitch-enum \
	-Wtype-limits \
	-Wundef \
	-Wuninitialized \
	-Wunknown-pragmas \
	-Wunsafe-loop-optimizations \
	-Wunused \
	-Wvarargs \
	-Wvariadic-macros \
	-Wvla \
	-Wvolatile-register-var \
	-Wwrite-strings \
	-pedantic-errors  \
	-std=gnu11

EXCEPTION_FLAGS = \
	-Wno-aggregate-return \
	-Wno-c++-compat \
	-Wno-unreachable-code \
	-Wno-variadic-macros \
	-Wno-trigraphs \

CFLAGS+= $(WARNING_FLAGS) $(EXCEPTION_FLAGS) -g

build: getarp

clean:
	$(RM) getarp

scrub: clean

valgrind: getarp
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--gen-suppressions=all \
		--show-reachable=yes \
		--error-limit=no \
		--error-exitcode=128 \
		./$< 192.168.1.24