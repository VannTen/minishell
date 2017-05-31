/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_set_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 15:02:56 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 12:18:08 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "path_constants.h"
#include "env_interface.h"
#include "builtins_interface.h"
#include <stdlib.h>

char	**set_path(t_shell *shell_state, const char *path_string)
{
	ft_free_string_array(&shell_state->path);
	shell_state->path = ft_strsplit(path_string, PATH_SEP);
	shell_state->persistent_path = TRUE;
	return (shell_state->path);
}

int		set_env(t_shell *shell, const char *setenv)
{
	char		*key;
	const char	*value;
	int			ret;

	ret = BUILTIN_EXIT_FAILURE;
	if (is_valid_setenv(setenv))
	{
		key = get_key(setenv);
		value = get_value(setenv);
		if (key != NULL && set_env_key(key, value, shell) == EXIT_SUCCESS)
			ret = BUILTIN_EXIT_SUCCESS;
	}
	return (ret);
}

int		set_env_key(const char *key, const char *value, t_shell *shell)
{
	char	**new_env;

	new_env = ft_putenv(key, value, shell->env);
	if (new_env != NULL)
	{
		shell->env = new_env;
		if (key_are_equal("PATH", key) && !(shell->persistent_path))
			ft_free_string_array(&shell->path);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int		unset_env(t_shell *shell, const char *key)
{
	if (ft_strchr(key, '=') == NULL)
	{
		shell->env = ft_removeenv(key, shell->env);
		if (ft_strcmp(key, "PATH") == 0 && !(shell->persistent_path))
			ft_free_string_array(&shell->path);
		return (BUILTIN_EXIT_SUCCESS);
	}
	else
		return (BUILTIN_EXIT_FAILURE);
}

void	empty_shell_env(t_shell *shell)
{
	shell->env = empty_env(shell->env);
	if (!shell->persistent_path)
		ft_free_string_array(&shell->path);
}
