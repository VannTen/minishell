/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 17:27:57 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/17 17:58:32 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>

char	*find_exec_path(char *exe_name, char **path)
{
	size_t	index;
	char	*exe_full_path;

	index = 0;
	exe_name = ft_strjoin("/", exe_name);
	while (path[index] != NULL)
	{
		exe_full_path = ft_strjoin(path[index], exe_name);
		ft_printf("Trying path : %s\n", exe_full_path);
		if (access(exe_full_path, F_OK) == 0)
			break ;
		else
			ft_strdel(&exe_full_path);
		index++;
	}
	if (exe_full_path == NULL)
		ft_printf("%s : not found\n", exe_name);
	return (exe_full_path);
}

int		exec_input(t_input com_and_args, char **path)
{
	pid_t	child_process;
	char	*exe_path;
	int		stat_loc;

	stat_loc = 0;
	child_process = fork();
	if (child_process == 0)
	{
		ft_printf("Child process before execve\n");
		exe_path = find_exec_path(com_and_args[0], path);
		if (exe_path == NULL)
			return (-1);
		execve(exe_path, com_and_args, NULL);
	}
	else if (child_process > 0)
	{
		ft_printf("Parent process\n");
		ft_free_string_array(&com_and_args);
		wait(&stat_loc);
	}
	return (stat_loc);
}
