/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 17:27:57 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 09:30:50 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_interface.h"
#include "shell_interface.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>

char	*find_exec_path(const char *exe_name, char *const *path)
{
	size_t	index;
	char	*exe_full_path;

	index = 0;
	exe_full_path = NULL;
	exe_name = ft_strjoin("/", exe_name);
	if (path != NULL)
	{
		while (path[index] != NULL)
		{
			exe_full_path = ft_strjoin(path[index], exe_name);
			if (access(exe_full_path, F_OK) == 0)
				break ;
			else
				ft_strdel(&exe_full_path);
			index++;
		}
	}
	if (exe_full_path == NULL)
		ft_dprintf(STDERR_FILENO, "%s : not found\n", exe_name);
	return (exe_full_path);
}

int		exec_command(t_input com_and_args, char *const *env, char *const *path)
{
	pid_t	child_process;
	int		stat_loc;
	char	*exe_path;

	stat_loc = 0;
	exe_path = find_exec_path(com_and_args[0], path);
	if (exe_path == NULL)
		return (-1);
	child_process = fork();
	if (child_process == 0)
		execve(exe_path, com_and_args, env);
	else if (child_process > 0)
		waitpid(child_process, &stat_loc, 0);
	return (stat_loc);
}

int		exec_input(t_input com_and_args, t_shell *shell_state)
{
	int			stat_loc;
	char	**path;
	char	**env;

	stat_loc = 0;
	stat_loc = search_for_builtin((const char **)com_and_args, shell_state);
	if (IS_BUILTIN(stat_loc))
		return (stat_loc);
	path = get_updated_path(shell_state);
	env = get_env(shell_state);
	return (exec_command(com_and_args, env, path));
}
