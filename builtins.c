/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 12:23:10 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "builtins_defs.h"
#include "shell_interface.h"
#include "libft.h"
#include "error_interface.h"
#include <stdlib.h>
#include <unistd.h>

static void	ft_builtin_error(const char *shell_name, const char *builtin,
		const char *arg,
		enum e_built_err err_code)
{
	int			precision;
	const char	*err_mess[] = {
		"not enough arguments",
		"ill-formed argument",
	};

	precision = err_code == BAD_ARG ? -1 : 0;
	ft_dprintf(STDERR_FILENO, "%1$s: %2$s: %3$.*6$s%4$.*6$s%5$s\n",
			shell_name, builtin, arg, ": ", err_mess[err_code], precision);
}

int			ft_echo(const char **argv, t_shell *shell)
{
	size_t	index;

	(void)shell;
	if (ft_strequ(argv[1], "-n"))
		index = 2;
	else
		index = 1;
	ft_print_string_array(argv + index, ' ');
	if (index == 1)
		ft_putchar('\n');
	return (BUILTIN_EXIT_SUCCESS);
}

int			ft_setenv(const char **argv, t_shell *shell)
{
	size_t	index;
	int		exit_status;

	exit_status = BUILTIN_EXIT_SUCCESS;
	index = 1;
	while (argv[index] != NULL && exit_status != BUILTIN_EXIT_SUCCESS)
	{
		exit_status = set_env(shell, argv[index]);
		index++;
	}
		if (exit_status != BUILTIN_EXIT_SUCCESS)
			ft_builtin_error(get_shell_name(shell), "setenv", argv[index - 1],
				BAD_ARG);
	if (index == 1)
	{
		exit_status = BUILTIN_EXIT_FAILURE;
		ft_builtin_error(get_shell_name(shell), "setenv", NULL,
				NOT_ENOUGH_ARGS);
	}
	return (exit_status);
}

int			ft_unsetenv(const char **argv, t_shell *shell)
{
	size_t	index;
	int		exit_status;

	index = 1;
	while (argv[index] != NULL)
	{
		exit_status = unset_env(shell, argv[1]);
		index++;
	}
	if (index == 1)
	{
		exit_status = BUILTIN_EXIT_FAILURE;
		ft_builtin_error(get_shell_name(shell), "unsetenv", NULL, NOT_ENOUGH_ARGS);
	}
	else
		exit_status = BUILTIN_EXIT_SUCCESS;
	return (exit_status);
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
