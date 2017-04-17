/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 17:27:57 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/17 18:17:48 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

void	search_for_builtin(char **cmd_ands_args)
{
	const char		*builtins[] = {
		"echo",
		"cd",
		"setenv",
		"unsetenv",
		"env",
		"exit"
	};
	const t_builtin	functions[] = {
		ft_echo,
		ft_cd,
		ft_setenv,
		ft_unsetenv,
		ft_env,
		ft_exit
	}:
}

int		exec_input(t_input com_and_args, char **path)
{
	pid_t	child_process;
	char	*exe_path;
	int		stat_loc;

	stat_loc = 0;
	search_for_builtin(com_and_args);
	child_process = fork();
	if (child_process == 0)
	{
		ft_printf("Child process before execve\n");
		exe_path = find_exec_path(com_and_args[0], path);
		if (exe_path == NULL)
			return (-1);
		execve(exe_path, com_and_args, environ);
	}
	else if (child_process > 0)
	{
		ft_printf("Parent process\n");
		ft_free_string_array(&com_and_args);
		wait(&stat_loc);
	}
	return (stat_loc);
}
