# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/19 07:58:53 by mgautier          #+#    #+#              #
#*   Updated: 2017/05/04 15:03:46 by mgautier         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

# Define target and sources

TARGET := minishell

SRC :=\
	main.c\
	shell.c\
	exec_command.c\
	builtin_env.c\
	env_tools.c\
	env_tools_get.c\
	env_tools_set.c\
	env_entry.c\
	builtins.c

# Directories

SRC_DIR :=
OBJ_DIR := object
INC_DIR := includes
DEP_DIR := .dep
TEST_DIR := test

# Dependencies

LIBRARY := libft 
OBJECTS :=
ELSE :=

# Sub directories

SUBDIRS :=
