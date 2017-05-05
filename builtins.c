/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 15:11:08 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "builtins_defs.h"
#include "shell_interface.h"
#include "libft.h"
#include <stddef.h>
#include <sys/param.h>

int	ft_echo(const char **argv, t_shell *shell_state)
{
	(void)shell_state;
	ft_print_string_array(argv + 1, ' ');
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}

int	ft_cd(const char **argv, t_shell *shell_state)
{
	const char	*home;
	const char	*arg;

	if (argv[1] == NULL)
	{
		home = get_env_value("HOME", get_env(shell_state));
		if (home == NULL)
			ft_dprintf(STDERR_FILENO, "%s: HOME not set", argv[0]);
		else
			arg = home;
	}
	else
		arg = argv[1];
	return (chdir(arg));
}

int	ft_exit(const char **argv, t_shell *shell_state)
{
	int	exit_status;

	if (argv[1] != NULL)
		exit_status = ft_atoi(argv[1]);
	else
		exit_status = EXIT_SUCCESS;
	set_exit_status(shell_state, exit_status);
	will_exit(shell_state);
	return (exit_status);
}

int	ft_setenv(const char **argv, t_shell *shell_state)
{
	set_env(shell_state, argv[1]);
	return (0);
}

int	ft_unsetenv(const char **argv, t_shell *shell_state)
{
	unset_env(shell_state, argv[1]);
	return (1);
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
