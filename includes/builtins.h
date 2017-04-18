/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:39:24 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/18 13:43:24 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

typedef	int		(*t_builtin)(t_input);
int 		ft_echo(char **argv);
int 		ft_cd(char **argv);
int 		ft_setenv(char **argv);
int 		ft_unsetenv(char **argv);
int 		ft_env(char **argv);
int 		ft_exit(char **argv);
#endif
