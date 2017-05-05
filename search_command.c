/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 09:48:30 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 11:57:32 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_interface.h"
#include "shell_interface.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>

/*
** Attempt to follow the POSIX specifications defined at
** http://pubs.opengroup.org/onlinepubs/9699919799/
** utilities/V3_chap02.html#tag_18_09_01_01
*/

char	*find_exe_path(const char *exe_name, char **const path)
{
	size_t	index;
	char	*exe_full_path;

	index = 0;
	exe_full_path = NULL;
	if (path != NULL)
	{
		while (path[index] != NULL)
		{
			exe_full_path = ft_strvajoin(3, path[index], "/", exe_name);
			if (access(exe_full_path, F_OK) == 0)
				break ;
			else
				ft_strdel(&exe_full_path);
			index++;
		}
	}
	return (exe_full_path);
}

int	execute_command(char *const *args, char **env)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == 0)
		execve(args[0], args, env);
	if (child > 0)
		waitpid(child, &status, 0);
	return (status);
}

int	search_and_execute_command(char **args, t_shell *shell_state)
{
	t_builtin	builtin_utility;
	char		*exe_name;

	if (!(string_has_char(args[0], '/')))
	{
		builtin_utility = search_for_builtin(args[0]);
		if (builtin_utility != NULL)
			return (builtin_utility((const char**)args, shell_state));
		else
		{
			exe_name = find_exe_path(args[0], get_path(shell_state));
			if (exe_name != NULL)
			{
				ft_strdel((char**)args);
				args[0] = exe_name;
			}
			else
			{
				ft_dprintf(STDERR_FILENO, "%s: command not found\n", args[0]);
				return (127);
			}
		}
	}
	return (execute_command(args, get_env(shell_state)));
}
