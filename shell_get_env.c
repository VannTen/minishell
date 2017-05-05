/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 15:02:23 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 15:03:40 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "env_interface.h"

char	**get_path(t_shell *shell_state)
{
	const char	*path_string;

	if (shell_state->path == NULL)
	{
		path_string = get_env_value("PATH", shell_state->env);
		if (path_string != NULL)
			shell_state->path = ft_strsplit(path_string, ':');
	}
	return (shell_state->path);
}

char	**get_env(t_shell *shell_state)
{
	return (shell_state->env);
}
