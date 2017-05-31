/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:44:36 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 14:15:51 by mgautier         ###   ########.fr       */
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

int	ft_echo(char const *const *argv, t_shell *shell);
int	ft_cd(char const *const *argv, t_shell *shell);
int	ft_setenv(char const *const *argv, t_shell *shell);
int	ft_unsetenv(char const *const *argv, t_shell *shell);
int	ft_env(char const *const *argv, t_shell *shell);
int	ft_exit(char const *const *argv, t_shell *shell);

#endif
