include settings.mk

################################################################################

outname = bin/$(1)

define compile_out
	$(CC) $(CFLAGS) -o "$@" $^ $(IDIRS:%=-I%) $(LIBDIRS:%=-L%) $(RUNDIRS:%=-Wl,-rpath,%) $(LIBS:%=-l%)
endef

define compile_objs
	$(CC) $(CFLAGS) -c -o "$@" $< $(IDIRS:%=-I%)
endef

################################################################################

# Project name
NAME=$(shell pwd | xargs -I{} basename "{}")

# Set compiler and archiver options
CC=gcc
AR=ar
ARFLAGS=rcs
MAKE=make --no-print-directory

# Set prerrequisites
SRCS_C += $(shell find src -iname "*.c")
SRCS_H += $(shell find src -iname "*.h")
DEPS = $(foreach SHL,$(SHARED_LIBPATHS),$(SHL:%=%/lib/lib$(notdir $(SHL)).so)) \
	$(foreach STL,$(STATIC_LIBPATHS),$(STL:%=%/lib/lib$(notdir $(STL)).a))

# Set header paths to (-I)nclude
IDIRS += $(addsuffix /src,$(SHARED_LIBPATHS) $(STATIC_LIBPATHS) .) /usr/local/include

# Set library paths to (-L)ook
LIBDIRS = $(addsuffix /lib,$(SHARED_LIBPATHS) $(STATIC_LIBPATHS)) /usr/local/lib

# Set shared library paths to be found in runtime (-rpath)
RUNDIRS = $(SHARED_LIBPATHS:%=$(shell pwd)/%/lib)

# Set intermediate objects
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS_C))

# Set output
OUT = $(call outname,$(NAME))

.PHONY: all
all: debug

.PHONY: debug
debug: CFLAGS = $(CDEBUG)
debug: $(OUT)

.PHONY: release
release: CFLAGS = $(CRELEASE)
release: $(OUT)

.PHONY: clean
clean:
	-rm -rfv $(dir $(TEST) $(OBJS) $(OUT))
	-for dir in $(SHARED_LIBPATHS) $(STATIC_LIBPATHS); do $(MAKE) -C $$dir clean; done

$(OUT): $(OBJS) | $(dir $(OUT))
	$(call compile_out)

obj/%.o: src/%.c $(SRCS_H) $(DEPS) | $(dir $(OBJS))
	$(call compile_objs)

.SECONDEXPANSION:
$(DEPS): $$(shell find $$(patsubst %lib/,%src/,$$(dir $$@)) -iname "*.c" -or -iname "*.h")
	$(MAKE) -C $(patsubst %lib/,%,$(dir $@)) 3>&1 1>&2 2>&3 | sed -E 's,(src/)[^ ]+\.(c|h)\:,$(patsubst %lib/,%,$(dir $@))&,' 3>&2 2>&1 1>&3

$(sort $(dir $(OUT) $(OBJS))):
	mkdir -pv $@
