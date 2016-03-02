#

# ============================================================================ #
# Directories

# Git submodule to init
MODULES				:= libft libftui
# Include dirs for .o dependencies
MKGEN_INCLUDESDIRS	:= include libft/include
# Obj files directory
MKGEN_OBJDIR		:= obj
# Makefiles to call (NAME variable req) (-> MKGEN_LIBSBIN_*)
MKGEN_LIBSDIRS_DEFAULT	:= libft
MKGEN_LIBSDIRS_GUI	:= libft libftui
# Source files (-> MKGEN_SRCSBIN_*)
MKGEN_SRCSDIRS_DEFAULT	:= srcs srcs_default
MKGEN_SRCSDIRS_GUI	:= srcs srcs_gui


# ============================================================================ #
# Default  flags
BASE_FLAGS		= -Wall -Wextra
HEAD_FLAGS		= $(addprefix -I,$(INCLUDEDIRS))
LD_FLAGS		= $(BASE_FLAGS) -Llibft -lft -o $@

MAKEFLAGS		+= -j


# ============================================================================ #
# Build mode
BUILD_MODE		= default
ifeq ($(BUILD_MODE),test)
	NAME			:= lemipc-test
	SRCSBIN			= $(MKGEN_SRCSBIN_TEST)
	LIBSBIN			= $(MKGEN_LIBSBIN_TEST)
	LIBSMAKE		= $(MKGEN_LIBSMAKE_TEST)
	INCLUDEDIRS		= $(MKGEN_INCLUDESDIRS)
	CC_LD			= $(CC_CPP)
	BASE_FLAGS		+= -O2
	LD_FLAGS		+= -lboost_unit_test_framework
else ifeq ($(BUILD_MODE),debug)
	NAME			:= lemipc
	SRCSBIN			= $(MKGEN_SRCSBIN_DEFAULT)
	LIBSBIN			= $(MKGEN_LIBSBIN_DEFAULT)
	LIBSMAKE		= $(MKGEN_LIBSDIRS_DEFAULT)
	INCLUDEDIRS		= $(MKGEN_INCLUDESDIRS)
	CC_LD			= $(CC_C)
	BASE_FLAGS		+= -g
else ifeq ($(BUILD_MODE),gui)
	NAME			:= lemipc-gui
	SRCSBIN			= $(MKGEN_SRCSBIN_GUI)
	LIBSBIN			= $(MKGEN_LIBSBIN_GUI)
	LIBSMAKE		= $(MKGEN_LIBSDIRS_GUI)
	INCLUDEDIRS		= $(MKGEN_INCLUDESDIRS)
	CC_LD			= $(CC_CPP)
	BASE_FLAGS		+= -O2 -DMAC_OS_MODE=1
	LD_FLAGS		+= -lglfw3 -framework OpenGL -Llibftui -lftui
else
	NAME			:= lemipc
	SRCSBIN			= $(MKGEN_SRCSBIN_DEFAULT)
	LIBSBIN			= $(MKGEN_LIBSBIN_DEFAULT)
	LIBSMAKE		= $(MKGEN_LIBSDIRS_DEFAULT)
	INCLUDEDIRS		= $(MKGEN_INCLUDESDIRS)
	CC_LD			= $(CC_C)
	BASE_FLAGS		+= -O2
endif


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
ifeq ($(UNAME),CYGWIN)
	CC_C		= x86_64-w64-mingw32-gcc
else
	CC_C		= clang
endif


# ============================================================================ #
# C++
CPP_FLAGS		= $(HEAD_FLAGS) $(BASE_FLAGS) -std=c++14
ifeq ($(UNAME),CYGWIN)
	CC_CPP		= x86_64-w64-mingw32-g++
	LD_FLAGS	+= -static
else
	CC_CPP		= clang++
endif


# ============================================================================ #
# Rules
# Default rule (needed to be before any include)
all: _all_git

-include $(DEPEND)

_all_git: $(MODULE_RULES)
	$(MAKE) _all_separate_compilation

_all_separate_compilation: $(LIBSMAKE) $(SRCSBIN)
	$(MAKE) _all_linkage

_all_linkage: $(NAME)

# Linking
$(NAME): $(LIBSBIN) $(SRCSBIN)
	$(CC_LD) $(LD_FLAGS) $(SRCSBIN) && $(PRINT_LINK)

# Compiling
$(MKGEN_OBJDIR)/%.o: %.c
	$(CC_C) $(C_FLAGS) -c $< -o $@ && $(PRINT_OK)
$(MKGEN_OBJDIR)/%.o: %.cpp
	$(CC_CPP) $(CPP_FLAGS) -c $< -o $@ && $(PRINT_OK)

# Init submodules
$(MODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

# Compile libs
$(LIBSMAKE):
	$(MAKE) -C $@

# Create obj directories
$(MKGEN_OBJDIR)/%/:
	mkdir -p $@

# Clean obj files
clean:
	rm -f $(SRCSBIN)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean
	$(MAKE) all


# ============================================================================ #
# Special targets
.SILENT:
.PHONY: all clean fclean re _all_git _all_separate_compilation _all_linkage $(LIBSMAKE)
