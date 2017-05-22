/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:54:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/17 11:31:07 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_INTERFACE_H
# define SHELL_INTERFACE_H
# include "libft.h"

/*
** Prompt shall be defined with printf style
*/

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
int		deinit_shell(t_shell **shell);

/*
** Shell state
** Implementation file : shell.c
*/

/*
** Shell env and path get
** Implementation file : shell_get_env.c
*/

char		**get_path(t_shell *shell_state);
char		**get_env(t_shell *shell_state);
const char	*get_shell_env_value(const char *key, const t_shell *shell);

/*
** Shell env and path set
** Implementation file : shell_set_env.c
*/

char	**set_path(t_shell *shell_state, const char *path_string);
void	set_env(t_shell *shell, const char *setenv);
void	set_env_key(const char *key, const char *value, t_shell *shell);
void	unset_env(t_shell *shell, const char *key);
void	empty_shell_env(t_shell *shell);

/*
** Get info about the shell state
** Implemenation file : shell_get.c
*/

t_bool	shall_exit(const t_shell *shell);
int		get_exit_status(const t_shell *shell);

/*
** Set state of the shell
** Implementation file : shell_set.c
*/

void	will_exit(t_shell *shell);
void	set_exit_status(t_shell *shell, int status);

/*
** Shell tools
** Implementation file : shell_tools.c
*/

void	prompt_user(const t_shell *shell);

#endif
