/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:54:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 13:46:53 by mgautier         ###   ########.fr       */
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
** Shell state initialization
** Implementation file : shell_init.c
*/

t_shell	*init_shell(const char **env);
void	deinit_shell(t_shell **shell);

/*
** Shell state
** Implementation file : shell.c
*/

char	**get_path(t_shell *shell_state);
char	**set_path(t_shell *shell_state, const char *path_string);
char	**get_env(t_shell *shell_state);
void	set_env(t_shell *shell, const char *setenv);
void	unset_env(t_shell *shell, const char *key);
void	empty_shell_env(t_shell *shell);

#endif
