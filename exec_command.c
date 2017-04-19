/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 17:27:57 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 15:12:30 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_interface.h"
#include "shell_interface.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>

extern char	**environ;

char	*find_exec_path(char *exe_name, char **path)
{
	size_t	index;
	char	*exe_full_path;

	index = 0;
	exe_name = ft_strjoin("/", exe_name);
	while (path[index] != NULL)
	{
		exe_full_path = ft_strjoin(path[index], exe_name);
		if (access(exe_full_path, F_OK) == 0)
			break ;
		else
			ft_strdel(&exe_full_path);
		index++;
	}
	if (exe_full_path == NULL)
		ft_dprintf(STDERR_FILENO, "%s : not found\n", exe_name);
	return (exe_full_path);
}

int		exec_command(t_input com_and_args, char **path)
{
	pid_t	child_process;
	int		stat_loc;
	char	*exe_path;

	stat_loc = 0;
	child_process = fork();
	if (child_process == 0)
	{
		exe_path = find_exec_path(com_and_args[0], path);
		if (exe_path == NULL)
			return (-1);
		execve(exe_path, com_and_args, environ);
	}
	else if (child_process > 0)
	{
		ft_free_string_array(&com_and_args);
		wait(&stat_loc);
	}
	return (stat_loc);

}

int		exec_input(t_input com_and_args, t_shell *shell_state)
{
	int		stat_loc;
	char	**path;

	stat_loc = 0;
	stat_loc = search_for_builtin(com_and_args);
	if (IS_BUILTIN(stat_loc))
		return (stat_loc);
	path = get_updated_path(shell_state);
	return (exec_command(com_and_args, path));
}
