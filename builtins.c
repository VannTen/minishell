/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/18 17:02:17 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include <stddef.h>
#include <sys/param.h>

int	ft_echo(char **argv)
{
	size_t	index;

	index = 1;
	while (argv[index] != NULL)
	{
		ft_putstr(argv[index]);
	index++;
	}
	ft_putchar('\n');
	return (EXIT_SUCCESS);
}

int	ft_cd(char **argv)
{
	return (chdir(argv[1]));
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
