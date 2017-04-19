/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 14:49:17 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 19:17:12 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "env_interface.h"

extern char	**environ;

t_shell	*init_shell(void)
{
	static t_shell	shell;

	shell.path = ft_string_array_dup((const char**)environ);
	shell.env = NULL;
	shell.env_has_changed_since_path_update = TRUE;
	return (shell.path != NULL ? &shell : NULL);
}

char	**get_updated_path(t_shell *shell_state)
{
	const char	*path_string;

	if (shell_state->env_has_changed_since_path_update)
	{
		ft_free_string_array(&shell_state->path);
		path_string = get_env_value("PATH");
		if (path_string != NULL)
			shell_state->path = ft_strsplit(path_string, ':');
		shell_state->env_has_changed_since_path_update = FALSE;
	}
	return (shell_state->path);
}

char	**get_env(t_shell *shell_state)
{
	return (shell_state->env);
}
