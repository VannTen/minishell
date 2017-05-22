/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_set_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 15:02:56 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/17 11:35:25 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "path_constants.h"
#include "env_interface.h"

char	**set_path(t_shell *shell_state, const char *path_string)
{
	ft_free_string_array(&shell_state->path);
	shell_state->path = ft_strsplit(path_string, PATH_SEP);
	shell_state->persistent_path = TRUE;
	return (shell_state->path);
}

void	set_env(t_shell *shell, const char *setenv)
{
	shell->env = ft_setenv_intern(shell->env, setenv);
	if (key_are_equal("PATH", setenv) && !(shell->persistent_path))
		ft_free_string_array(&shell->path);
}

void	set_env_key(const char *key, const char *value, t_shell *shell)
{
	shell->env = ft_putenv(key, value, shell->env);
	if (key_are_equal("PATH", key) && !(shell->persistent_path))
		ft_free_string_array(&shell->path);
}

void	unset_env(t_shell *shell, const char *key)
{
	shell->env = ft_removeenv(key, shell->env);
	if (ft_strcmp(key, "PATH") == 0 && !(shell->persistent_path))
		ft_free_string_array(&shell->path);
}

void	empty_shell_env(t_shell *shell)
{
	shell->env = empty_env(shell->env);
	if (!shell->persistent_path)
		ft_free_string_array(&shell->path);
}
