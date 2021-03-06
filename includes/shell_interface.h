/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:54:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 16:31:21 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_INTERFACE_H
# define SHELL_INTERFACE_H
# include "libft.h"

/*
** Prompt shall be defined with printf style
*/

typedef struct s_shell	t_shell;

/*
** Commands search
** Implementation file : search_command.c
*/

int					search_and_execute_command(char const *const *args,
		t_shell *shell);
int					search_external_command(char const *const *args,
		t_shell *shell);

/*
** Commands execution
** Implementation file : execute_command.c
*/

int					execute_command(const char *command_path,
		char const *const *args, char const *const *env);

/*
** Shell state initialization
** Implementation file : shell_init.c
*/

t_shell				*init_shell(char const *const *env, const char *shell_name);
int					deinit_shell(t_shell **shell);

/*
** Shell state
** Implementation file : shell.c
*/

/*
** Shell env and path get
** Implementation file : shell_get_env.c
*/

char const *const	*get_path(t_shell *shell);
char const *const	*get_env(t_shell *shell);
const char			*get_shell_env_value(const char *key, const t_shell *shell);

/*
** Shell env and path set
** Implementation file : shell_set_env.c
*/

char				**set_path(t_shell *shell, const char *path_string);
int					set_env(t_shell *shell, const char *setenv);
int					set_env_key(const char *key, const char *value,
		t_shell *shell);
int					unset_env(t_shell *shell, const char *key);
void				empty_shell_env(t_shell *shell);

/*
** Get info about the shell state
** Implemenation file : shell_get.c
*/

t_bool				shall_exit(const t_shell *shell);
int					get_exit_status(const t_shell *shell);
const char			*get_shell_name(const t_shell *shell);

/*
** Set state of the shell
** Implementation file : shell_set.c
*/

void				will_exit(t_shell *shell);
void				set_exit_status(t_shell *shell, int status);
void				set_shell_name(t_shell *shell, const char *prog_path);

/*
** PWD tools
** Implementation file : shell_pwd_tools.c
*/

const char			*get_pwd(t_shell *shell);
const char			*update_pwd(const char *new_pwd, t_shell *shell);

/*
** Shell tools
** Implementation file : shell_tools.c
*/

void				prompt_user(t_shell *shell);

#endif
