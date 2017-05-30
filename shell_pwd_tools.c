/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pwd_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:24:07 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/30 19:09:30 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_interface.h"
#include <unistd.h>
#include <stdlib.h>

const char	*intern_upd_pwd(const char *new_pwd, t_shell *shell)
{
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		if (set_env_key("PWD", cwd, shell) == EXIT_FAILURE)
			new_pwd = NULL;
		ft_strdel(&cwd);
	}
	else
		new_pwd = NULL;
	return (new_pwd);
}

const char	*update_pwd(const char *new_pwd, t_shell *shell)
{
	const char	*old_pwd;

	old_pwd = get_pwd(shell);
	if (old_pwd == NULL ||
			set_env_key("OLDPWD", old_pwd, shell) == EXIT_FAILURE)
		return (NULL);
	if (new_pwd != NULL)
	{
		if (set_env_key("PWD", new_pwd, shell) == EXIT_FAILURE)
			new_pwd = NULL;
	}
	else
		new_pwd = intern_upd_pwd(new_pwd, shell);
	return (new_pwd);
}

const char	*get_pwd(t_shell *shell)
{
	const char	*pwd;
	char		*pwd_sys;

	pwd = get_shell_env_value("PWD", shell);
	if (pwd == NULL)
	{
		pwd_sys = getcwd(NULL, 0);
		if (pwd_sys != NULL)
		{
			if (set_env_key("PWD", pwd_sys, shell) == EXIT_SUCCESS)
				pwd = pwd_sys;
			else
				pwd = NULL;
		}
		ft_strdel(&pwd_sys);
	}
	return (pwd);
}
