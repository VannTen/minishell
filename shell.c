/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 14:49:17 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 15:08:36 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "env_interface.h"

t_shell	*init_shell(void)
{
	static t_shell	shell;

	shell.env = NULL;
	shell.path = NULL;
	shell.env_has_changed = TRUE;
	return (&shell);
}

char		**get_updated_path(t_shell *shell_state)
{
	const char	*path_string;

	if (shell_state->env_has_changed)
	{
		ft_free_string_array(&shell_state->path);
		path_string = get_env_value("PATH");
		if (path_string != NULL)
			shell_state->path = ft_strsplit(path_string, ':');
	}
	return (shell_state->path);
}
