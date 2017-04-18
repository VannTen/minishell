/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:24:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/18 20:57:11 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "builtins.h"
#include "libft.h"
#include <stddef.h>
#include <sys/param.h>

extern char	**environ;

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
	static t_bool	environ_is_allocated = FALSE;
	char			**tmp_environ;
	char			*key_entry;
	char			*env_entry;

	if (argv[1] != NULL)
	{
		key_entry = get_key(env_entry);
		if (key_entry != NULL)
		{
			env_entry = get_env_
			if (ft_strlen(argv[1] + ft_strlen(key_entry) + 1)
					<= ft_strlen(get_env_value(key_entry))
					ft_strcpy(
		}
	}
	if (!environ_is_allocated)
	{
		tmp_environ = ft_string_array_dup((const char **)environ);
		if (tmp_environ == NULL)
			return (-1);
		else
		{
			environ = tmp_environ;
			environ_is_allocated = TRUE;
		}
	}
	else
		free(environ);
	return (1);
}

int	ft_unsetenv(char **argv)
{
	ft_putendl(argv[0]);
	return (1);
}

int	ft_env(char **argv)
{
	(void)argv;
	ft_print_string_array(environ, '\n');
	return (1);
}
