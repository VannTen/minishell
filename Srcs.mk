# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/19 07:58:53 by mgautier          #+#    #+#              #
#*   Updated: 2017/05/31 12:46:28 by mgautier         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# Define target and sources

TARGET := minishell

#BUILTIN_ENV = $(NOTHING)
#BUILTIN_CD = $(NOTHING)
#BUILTIN_EXIT = $(NOTHING)
#BUILTINS = $(NOTHING)
#ENV_TOOLS = $(NOTHING)
#MY_SHELL = $(NOTHING)
#SHELL_INPUT = $(NOTHING)
#MAIN = $(NOTHING)

BUILTIN_EXIT ?=\
	builtin_exit.c
BUILTIN_ENV ?=\
	builtin_env.c\
	builtin_env_intern.c\
	builtin_env_options.c
BUILTIN_CD ?=\
	builtin_cd.c\
	builtin_cd_intern.c\
	builtin_cd_intern_operand.c
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
	shell_tools.c\
	shell_pwd_tools.c
SHELL_INPUT ?=\
	input.c\
	input_error.c
BUILTINS ?=\
	builtins_search.c\
	builtins.c
MAIN ?=\
	main.c\
	search_command.c\
	execute_command.c
SRC :=\
	$(MAIN)\
	$(BUILTINS)\
	$(BUILTIN_EXIT)\
	$(BUILTIN_ENV)\
	$(BUILTIN_CD)\
	$(ENV_TOOLS)\
	$(MY_SHELL)\
	$(SHELL_INPUT)

# Directories

SRC_DIR :=
OBJ_DIR := object
INC_DIR := includes
DEP_DIR := .dep
TEST_DIR := test
