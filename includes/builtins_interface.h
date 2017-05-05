/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_interface.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:39:24 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 11:09:41 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_INTERFACE_H
# define BUILTINS_INTERFACE_H
# include "shell_interface.h"
# define IS_BUILTIN(x) (x != -1)

typedef	int		(*t_builtin)(const char**, t_shell*);

t_builtin		search_for_builtin(const char *cmd);

#endif
