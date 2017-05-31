/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:44:36 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 12:07:18 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_DEFS_H
# define BUILTINS_DEFS_H
# include "builtins_interface.h"
# include "shell_interface.h"

enum	e_built_err
{
	NOT_ENOUGH_ARGS,
	BAD_ARG
};

int	ft_echo(const char **argv, t_shell *shell);
int	ft_cd(const char **argv, t_shell *shell);
int	ft_setenv(const char **argv, t_shell *shell);
int	ft_unsetenv(const char **argv, t_shell *shell);
int	ft_env(const char **argv, t_shell *shell);
int	ft_exit(const char **argv, t_shell *shell);

#endif
