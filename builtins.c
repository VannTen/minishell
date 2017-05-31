/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 16:27:01 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "builtins_defs.h"
#include "shell_interface.h"
#include "libft.h"
#include "error_interface.h"
#include <stdlib.h>
#include <unistd.h>

int			ft_echo(char const *const *argv, t_shell *shell)
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

static int	change_env(char const *const *argv, t_shell *shell,
		int (*setter)(t_shell*, const char*))
{
	size_t	index;
	int		exit_status;

	exit_status = BUILTIN_EXIT_SUCCESS;
	index = 1;
	while (argv[index] != NULL && exit_status == BUILTIN_EXIT_SUCCESS)
	{
		exit_status = setter(shell, argv[index]);
		index++;
	}
	if (exit_status != BUILTIN_EXIT_SUCCESS)
		ft_shell_error(get_shell_name(shell), argv[0], argv[index - 1],
				BAD_ARG);
	if (index == 1)
	{
		exit_status = BUILTIN_EXIT_FAILURE;
		ft_shell_error(get_shell_name(shell), argv[0], NULL,
				NOT_ENOUGH_ARGS);
	}
	return (exit_status);
}

int			ft_setenv(char const *const *argv, t_shell *shell)
{
	return (change_env(argv, shell, set_env));
}

int			ft_unsetenv(char const *const *argv, t_shell *shell)
{
	return (change_env(argv, shell, unset_env));
}
