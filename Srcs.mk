# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/19 07:58:53 by mgautier          #+#    #+#              #
#*   Updated: 2017/05/10 17:10:04 by mgautier         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# Define target and sources

TARGET := minishell

#BUILTIN_ENV = $(NOTHING)
#BUILTIN_CD = $(NOTHING)
#ENV_TOOLS = $(NOTHING)
#MY_SHELL = $(NOTHING)

BUILTIN_ENV ?=\
	builtin_env.c\
	builtin_env_intern.c\
	builtin_env_options.c
BUILTIN_CD ?=\
	builtin_cd.c
ENV_TOOLS ?=\
	env_tools.c\
	env_tools_get.c\
	env_tools_set.c\
	env_entry.c
MY_SHELL ?=\
	shell_get.c\
	shell_set.c\
	shell_set_env.c\
	shell_get_env.c\
	shell_init.c\
	shell_tools.c
SRC :=\
	main.c\
	search_command.c\
	builtins.c\
	$(BUILTIN_ENV)\
	$(BUILTIN_CD)\
	$(ENV_TOOLS)\
	$(MY_SHELL)

# Directories

SRC_DIR :=
OBJ_DIR := object
INC_DIR := includes
DEP_DIR := .dep
TEST_DIR := test
