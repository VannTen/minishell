/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:44:36 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/03 15:49:56 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_DEFS_H
# define BUILTINS_DEFS_H
# include "builtins_interface.h"
# include "shell_interface.h"

typedef	int		(*t_builtin)(t_input, t_shell*);
int 		ft_echo(char **argv, t_shell *shell_state);
int 		ft_cd(char **argv, t_shell *shell_state);
int 		ft_setenv(char **argv, t_shell *shell_state);
int 		ft_unsetenv(char **argv, t_shell *shell_state);
int 		ft_env(const char **argv, t_shell *shell_state);
int 		ft_exit(char **argv, t_shell *shell_state);

#endif
