/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_interface.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 13:39:24 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 14:14:46 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_INTERFACE_H
# define BUILTINS_INTERFACE_H
# include "shell_interface.h"

enum
{
	BUILTIN_EXIT_SUCCESS,
	BUILTIN_EXIT_FAILURE
};

typedef	int		(*t_builtin)(char const *const *, t_shell*);

/*
** Search the appropriate builtin and returns it (as a function pointer)
** or NULL if no buitin is found.
** Implementation file : builtins_search.c
*/

t_builtin		search_for_builtin(const char *cmd);

#endif
