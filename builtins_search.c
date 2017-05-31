/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_search.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 12:43:02 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 12:43:57 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_defs.h"
#include "libft.h"

t_builtin	search_for_builtin(const char *cmd)
{
	const char		*builtins[] = {
		"echo",
		"cd",
		"setenv",
		"unsetenv",
		"env",
		"exit",
		NULL
	};
	const t_builtin	functions[] = {
		ft_echo,
		ft_cd,
		ft_setenv,
		ft_unsetenv,
		ft_env,
		ft_exit,
		NULL
	};
	size_t			index;

	index = 0;
	while (builtins[index] != NULL && !ft_strequ(cmd, builtins[index]))
		index++;
	return (functions[index]);
}
