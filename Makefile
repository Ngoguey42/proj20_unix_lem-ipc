#

# ============================================================================ #
# Directories

# Executable name
NAME			:= lemipc
# Git submodule to init
MODULES			:= libft
# Makefiles to call
LIBS			:= libft

INCLUDE_DIRS	= include libft/include
SRCS_DIRS		= srcs
O_DIR			:= obj


# ============================================================================ #
# Default  flags / compilers
BASE_FLAGS		= -Wall -Wextra
HEAD_FLAGS		= $(addprefix -I,$(INCLUDE_DIRS))
LD_FLAGS		= $(BASE_FLAGS) -Llibft -lft -o $@

CC_LD			= $(CC_C)

MAKEFLAGS		+= -j


# ============================================================================ #
# Build mode
BUILD_MODE		= build
ifeq ($(BUILD_MODE),test)
	SRCS_DIRS		+= srcs_test
	LD_FLAGS		+= -lboost_unit_test_framework
	BASE_FLAGS		+= -O2
else ifeq ($(BUILD_MODE),debug)
	SRCS_DIRS		+= srcs_build
	BASE_FLAGS		+= -g
else
	SRCS_DIRS		+= srcs_build
	BASE_FLAGS		+=
endif

# legacy with makemake ===========================
DIRS			:= srcs srcs_build
# DEBUG_MODE		?= 0
# export DEBUG_MODE
# /legacy with makemake ===========================


# ============================================================================ #
# Misc
UNAME			:= $(shell uname | cut -c1-6)
PRINT_OK		= printf '\033[32m$<\033[0m\n'
PRINT_LINK		= printf '\033[32m$@\033[0m\n'
DEPEND			:= depend.mk
MODULE_RULES	:= $(addsuffix /.git,$(MODULES))
SHELL			:= /bin/bash


# ============================================================================ #
# C
C_FLAGS			= $(HEAD_FLAGS) $(BASE_FLAGS)
ifeq ($(UNAME),Cygwin)
	CC_C		= x86_64-w64-mingw32-gcc
else
	CC_C		= clang
endif


# ============================================================================ #
# C++
CPP_FLAGS		= $(HEAD_FLAGS) $(BASE_FLAGS) -std=c++14
ifeq ($(UNAME),Cygwin)
	CC_CPP		= x86_64-w64-mingw32-g++
	LD_FLAGS	+= -static
else
	CC_CPP		= clang++
endif


# ============================================================================ #
HEAD_FLAGS := $(HEAD_FLAGS)
C_FLAGS := $(C_FLAGS)
CPP_FLAGS := $(CPP_FLAGS)

CC_C := $(CC_C)
CC_CPP := $(CC_CPP)

# ============================================================================ #
# Rules
# Default rule (need to be before any include)
all: _all1

# Include $(O_FILES) and dependencies
-include $(DEPEND)

_all1: $(MODULE_RULES)
	$(MAKE) _all2

_all2: libs $(O_FILES)
	$(MAKE) _all3

_all3: $(NAME)

# Linking
$(NAME): $(LIBS_DEPEND) $(O_FILES)
	$(CC_LD) $(LD_FLAGS) $(O_FILES) && $(PRINT_LINK)

# Compiling
$(O_DIR)/%.o: %.c
	$(CC_C) $(C_FLAGS) -c $< -o $@ && $(PRINT_OK)
$(O_DIR)/%.o: %.cpp
	$(CC_CPP) $(CPP_FLAGS) -c $< -o $@ && $(PRINT_OK)

# Init submodules
$(MODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

# Create obj directories
$(O_DIR)/%/:
	mkdir -p $@

# Clean obj files
clean:
	rm -f $(O_FILES)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean
	$(MAKE) all


# ============================================================================ #
# Special targets
.SILENT:
.PHONY: all clean fclean re _all1 _all2 _all3
