/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 11:50:31 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "builtins_defs.h"
#include "shell_interface.h"
#include "libft.h"
#include "error_interface.h"
#include <stdlib.h>

int			ft_echo(const char **argv, t_shell *shell_state)
{
	(void)shell_state;
	ft_print_string_array(argv + 1, ' ');
	ft_putchar('\n');
	return (BUILTIN_EXIT_SUCCESS);
}

int			ft_setenv(const char **argv, t_shell *shell_state)
{
	return (set_env(shell_state, argv[1]));
}

int			ft_unsetenv(const char **argv, t_shell *shell_state)
{
	unset_env(shell_state, argv[1]);
	return (0);
}

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
	while (builtins[index] != NULL && ft_strcmp(cmd, builtins[index]) != 0)
		index++;
	return (functions[index]);
}
