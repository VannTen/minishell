/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:54:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 11:45:07 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_INTERFACE_H
# define SHELL_INTERFACE_H

/*
** Prompt shall be defined with printf style
*/

# define PROMPT "\n$>"

typedef struct s_shell	t_shell;
typedef char**			t_input;

/*
** Commands execution
** Implementation file : exec_command.c
*/

int		search_and_execute_command(char **args, t_shell *shell_state);

/*
** Shell state modification
** Implementation file : shell.c
*/

t_shell	*init_shell(const char **env);
void	deinit_shell(t_shell **shell);
char	**get_path(t_shell *shell_state);
char	**force_path(t_shell *shell_state, const char *path_string);
void	get_inherited_env(t_shell *shell_state);
char	**get_env(t_shell *shell_state);

#endif
