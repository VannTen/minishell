/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_interface.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:39:24 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 11:46:07 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_INTERFACE_H
# define BUILTINS_INTERFACE_H
# include "minishell.h"
# define IS_BUILTIN(x) (x != -1)

int		search_for_builtin(char **cmd_and_args);

#endif
