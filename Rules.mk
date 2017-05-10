#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Rules.mk                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2016/12/13 19:41:31 by mgautier          #+#    #+#             *#
#*   Updated: 2017/05/10 18:42:28 by mgautier         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

##
## Rules.mk
## One instance of this file is included for every subdirectory of the project
## which produces one target (directory that hold specific type of files, such
## as source directory, includes directory, or objects directory,
## aren't concerned
##

STACK_POINTER := $(STACK_POINTER).x
DIR_$(STACK_POINTER) := $(DIR)
DIR := $(DIR)$(SUBDIR)

$(info Begin parsing $(DIR)Rules.mk)

# Includes Srcs.mk, which defines directory data (source files, target name,
# additional dependencies, libraries needed)
# Clean variables before, so we dont catch some from a previous dir
# if there is a problem with Srcs.mk

$(call CLEAR_VAR_LIST, $(EMPTY_SRCS.MK))
include $(DIR)Srcs.mk

# Give the full path to the locals directories (by appending DIR before them)
# add a slash only if necessary
# (alway adding a slash cause trouble in the top level
# directory if subdirs are not defined
# (which means SRC_DIR (or another one)= DIR)

OBJ_DIR := $(BUILD_PREFIX)$(OBJ_DIR)
$(foreach TYPE,SRC OBJ DEP INC,$(eval $(call ADD_SLASH,$(TYPE))))
# Standard expansion of the SRC into the local OBJ and DEP
# + add them to clean-up variables

OBJ_$(DIR) := $(OBJ)
DEP_$(DIR) := $(DEP)

TARGET_$(DIR) := $(DIR)$(BUILD_PREFIX)$(TARGET)

# Include additionnal deps from a separate file

$(call CLEAR_VAR_LIST, $(EMPTY_DEPS.MK))
include $(DIR)Dependencies.mk
$(TARGET): LIB_INCLUDES := $(LIBRARY)
LIBS_$(DIR) := $(LIBRARY)

# Inclusion of subdirs Rules.mk

$(foreach SUBDIR,$(addsuffix /,$(LIBRARY)),$(eval $(INCLUDE_SUBDIRS)))
$(foreach SUBDIR,$(addsuffix /,$(SUBDIRS)),$(eval $(INCLUDE_SUBDIRS)))


# Add the obj and dependency dir to the list of generated dir
# only if they are different from the DIR (which is not generated)

ifdef OBJ_DIR
GENERATED_SUBDIRS += $(OBJ_LOCAL_$(DIR))
endif
ifdef DEP_DIR
GENERATED_SUBDIRS += $(DEP_LOCAL_$(DIR))
endif

# + check if the target of this directory is indicated
# If it is, a vpath directive allow rules that use that target
# as a prerequisites to locate it easily

ifdef TARGET_$(DIR)
vpath $(notdir $(TARGET_$(DIR))) $(DIR)
$(basename $(TARGET_$(DIR)))_PATH := $(DIR)
else
$(eval $(TARGET_$(DIR)_ERROR))
endif

# If the target is a static library, use the approriate recipe.
# Otherwise, use the linker for an executable

ifeq ($(suffix $(TARGET_$(DIR))),.a)
$(TARGET_$(DIR)): RECIPE = $(LINK_STATIC_LIB)
LIBPATH_INC += $(DIR)
else ifeq ($(suffix $(TARGET_$(DIR))),.so)
$(TARGET_$(DIR)): RECIPE = $(LINK_SHARED_LIB)
LIBPATH_INC += $(DIR)
else
$(TARGET_$(DIR)): RECIPE = $(LINK_EXE)
endif

# Local rules

$(TARGET_$(DIR)): $(OBJ_$(DIR)) $(ELSE) $(patsubst lib%,-l$(BUILD_PREFIX)%,$(LIBS_$(DIR)))
	$(QUIET) $(RECIPE)

$(eval $(STATIC_OBJ_RULE))

# If the target is different from the one make is invoked in,
# add it to the search path for headers.
# If the target requiers a library, add its directory too.

$(TARGET_$(DIR)): DIR := $(DIR)
ifneq ($(INC_LOCAL_$(DIR)),)
$(TARGET_$(DIR)): INCLUDE := $(INC_LOCAL_$(DIR)) $(if $(DIR),$(DIR),.)
else
$(TARGET_$(DIR)): INCLUDE :=
endif

ifdef LIBRARIES
$(DIR)_LIBS := $(LIBRARIES)
$(TARGET_$(DIR)): LIB_INCLUDES = $(foreach XXX,$($(DIR)_LIBS),$($(XXX)_PATH))
endif

# Clean variables 
# If this is not the top level (the one where make is invoked) add the Makefile
# and the Rules.mk files to MKCLEAN
# That way, we're sure that the top level Makefiles are preserved.

CLEAN += $(OBJ_$(DIR))
FCLEAN += $(TARGET_$(DIR)) $(DEP_$(DIR))
ifneq ($(DIR),)
MKCLEAN += $(DIR)Makefile $(DIR)Rules.mk
endif

# Inclusion of depency files (auto-generated)

DEP_FILES += $(DEP_$(DIR))

# Tracking current directory

$(info Finish parsing $(DIR)Rules.mk)
DIR := $(DIR_$(STACK_POINTER))
STACK_POINTER := $(basename $(STACK_POINTER))
