/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 10:59:27 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "builtins_defs.h"
#include "shell_defs.h"
#include "libft.h"
#include <stddef.h>
#include <sys/param.h>

extern char	**environ;

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
	(void)shell_state;

	if (argv[1] == NULL)
	{
		home = get_env_value("HOME");
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
	(void)shell_state;

	if (argv[1] != NULL)
		exit_status = ft_atoi(argv[1]);
	else
		exit_status = EXIT_SUCCESS;
	exit(exit_status);
	return (exit_status);
}

int	ft_setenv(const char **argv, t_shell *shell_state)
{
	shell_state->env = ft_setenv_intern(shell_state->env, argv[0]);
	return (0);
}

int	ft_unsetenv(const char **argv, t_shell *shell_state)
{
	(void)shell_state;
	ft_putendl(argv[0]);
	return (1);
}

int		search_for_builtin(const char **cmd_and_args, t_shell *shell_state)
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
		ft_exit
	};
	size_t	index;

	index = 0;
	while (builtins[index] != NULL
			&& ft_strcmp(cmd_and_args[0], builtins[index]) != 0)
		index++;
	if (builtins[index] == NULL)
		return (-1);
	else
		return (functions[index](cmd_and_args, shell_state));
}
