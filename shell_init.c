/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:10:34 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 16:14:41 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"

t_shell	*init_shell(const char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (shell != NULL)
	{
		shell->env = ft_string_array_dup(env);
		shell->path = NULL;
		shell->persistent_path = FALSE;
		shell->shall_exit = FALSE;
		shell->exit_status = 0;
		if (shell->env == NULL)
			deinit_shell(&shell);
	}
	return (shell);
}

int		deinit_shell(t_shell **shell)
{
	int		exit_status;
	t_shell	*to_del;

	to_del = *shell;
	if (to_del != NULL)
	{
		exit_status = to_del->exit_status;
		ft_free_string_array(&to_del->env);
		ft_free_string_array(&to_del->path);
		free(to_del);
		*shell = NULL;
	}
	else
		exit_status = -1;
	return (exit_status);
}
