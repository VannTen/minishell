/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:54:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 15:11:12 by mgautier         ###   ########.fr       */
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

int		exec_input(t_input com_and_args, t_shell *shell_state);
t_shell	*init_shell(void);
char	**get_updated_path(t_shell *shell_state);
#endif
