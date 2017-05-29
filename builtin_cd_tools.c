/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 17:24:07 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 17:26:57 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_interface.h"
#include <unistd.h>

void	update_pwd(const char *new_pwd, t_shell *shell)
{
	const char	*old_pwd;
	char		*cwd;

	old_pwd = get_shell_env_value("PWD", shell);
	set_env_key("OLDPWD", old_pwd, shell);
	if (new_pwd != NULL)
		set_env_key("PWD", new_pwd, shell);
	else
	{
		cwd = getcwd(NULL, 0);
		set_env_key("PWD", cwd, shell);
		ft_strdel(&cwd);
	}
}
