/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pwd_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:24:07 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/30 17:30:48 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_interface.h"
#include <unistd.h>

const char	*update_pwd(const char *new_pwd, t_shell *shell)
{
	const char	*old_pwd;
	char		*cwd;

	old_pwd = get_pwd(shell);
	set_env_key("OLDPWD", old_pwd, shell);
	if (new_pwd != NULL)
		set_env_key("PWD", new_pwd, shell);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd != NULL)
		{
			set_env_key("PWD", cwd, shell);
			ft_strdel(&cwd);
		}
		else
			new_pwd == NULL;
	}
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
			set_env_key("PWD", pwd_sys, shell);
			pwd = pwd_sys;
		}
		ft_strdel(&pwd_sys);
	}
	return (pwd);
}
