/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:54:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 13:32:17 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_INTERFACE_H
# define SHELL_INTERFACE_H

/*
** Prompt shall be defined with printf style
*/

# define PROMPT "$>"

typedef struct s_shell	t_shell;
typedef char**			t_input;

/*
** Commands execution
** Implementation file : exec_command.c
*/

int		exec_input(t_input com_and_args, char **path);
#endif
