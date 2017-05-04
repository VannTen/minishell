/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 14:49:17 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 15:05:32 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "env_interface.h"


t_shell	*init_shell(const char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (shell != NULL)
	{
		shell->env = ft_string_array_dup(env);
		shell->path = NULL;
		shell->env_has_changed_since_path_update = TRUE;
		if (shell->env == NULL)
			deinit_shell(&shell);
	}
	return (shell);
}

void	deinit_shell(t_shell **shell)
{
	t_shell	*to_del;

	to_del = *shell;
	if (to_del != NULL)
	{
		ft_free_string_array(&to_del->env);
		ft_free_string_array(&to_del->path);
		free(to_del);
		*shell = NULL;
	}
}

char	**get_updated_path(t_shell *shell_state)
{
	const char	*path_string;

	if (shell_state->env_has_changed_since_path_update)
	{
		ft_free_string_array(&shell_state->path);
		path_string = get_env_value("PATH", shell_state->env);
		if (path_string != NULL)
			shell_state->path = ft_strsplit(path_string, ':');
		shell_state->env_has_changed_since_path_update = FALSE;
	}
	return (shell_state->path);
}

char	**force_path(t_shell *shell_state, const char *path_string)
{
	ft_free_string_array(&shell_state->path);
	shell_state->path = ft_strsplit(path_string, PATH_SEP);
	shell_state->env_has_changed_since_path_update = FALSE;
	return (shell_state->path);
}

char	**get_env(t_shell *shell_state)
{
	return (shell_state->env);
}
