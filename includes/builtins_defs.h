/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:44:36 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 11:44:51 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_DEFS_H
# define BUILTINS_DEFS_H
# include "builtins_interface.h"

typedef	int		(*t_builtin)(t_input);
int 		ft_echo(char **argv);
int 		ft_cd(char **argv);
int 		ft_setenv(char **argv);
int 		ft_unsetenv(char **argv);
int 		ft_env(char **argv);
int 		ft_exit(char **argv);

#endif
