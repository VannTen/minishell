/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 14:05:35 by mgautier         ###   ########.fr       */
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
	size_t	index;
	int		exit_status;

	exit_status = BUILTIN_EXIT_SUCCESS;
	index = 1;
	while (argv[index] != NULL && exit_status == BUILTIN_EXIT_SUCCESS)
	{
		exit_status = set_env(shell_state, argv[index]);
		index++;
	}
	return (exit_status);
}

int			ft_unsetenv(const char **argv, t_shell *shell_state)
{
	size_t	index;

	index = 1;
	while (argv[index] != NULL)
	{
		unset_env(shell_state, argv[1]);
		index++;
	}
	return (BUILTIN_EXIT_SUCCESS);
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
