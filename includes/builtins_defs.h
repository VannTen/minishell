/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:44:36 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 10:41:06 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_DEFS_H
# define BUILTINS_DEFS_H
# include "builtins_interface.h"
# include "shell_interface.h"

typedef	int		(*t_builtin)(const char**, t_shell*);
int 		ft_echo(const char **argv, t_shell *shell_state);
int 		ft_cd(const char **argv, t_shell *shell_state);
int 		ft_setenv(const char **argv, t_shell *shell_state);
int 		ft_unsetenv(const char **argv, t_shell *shell_state);
int 		ft_env(const char **argv, t_shell *shell_state);
int 		ft_exit(const char **argv, t_shell *shell_state);

#endif
