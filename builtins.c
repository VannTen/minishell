/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/18 18:44:43 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "builtins.h"
#include "libft.h"
#include <stddef.h>
#include <sys/param.h>

int	ft_echo(char **argv)
{
	ft_print_string_array(argv + 1, ' ');
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}

int	ft_cd(char **argv)
{
	const char	*home;
	const char	*arg;

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

int	ft_exit(char **argv)
{
	int	exit_status;

	if (argv[1] != NULL)
		exit_status = ft_atoi(argv[1]);
	else
		exit_status = EXIT_SUCCESS;
	exit(exit_status);
	return (exit_status);
}

int	ft_setenv(char **argv)
{
	ft_putendl(argv[0]);
	return (1);
}

int	ft_unsetenv(char **argv)
{
	ft_putendl(argv[0]);
	return (1);
}

int	ft_env(char **argv)
{
	ft_putendl(argv[0]);
	return (1);
}
