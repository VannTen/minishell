/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 15:02:23 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 14:28:35 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "env_interface.h"

char const *const	*get_path(t_shell *shell_state)
{
	const char	*path_string;

	if (shell_state->path == NULL)
	{
		path_string = get_env_value("PATH", shell_state->env);
		if (path_string != NULL)
			shell_state->path = ft_strsplit(path_string, ':');
	}
	return ((char const *const *)shell_state->path);
}

char const *const	*get_env(t_shell *shell_state)
{
	return ((char const *const *)shell_state->env);
}

const char			*get_shell_env_value(const char *key, const t_shell *shell)
{
	return (get_env_value(key, shell->env));
}
