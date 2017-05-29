/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:03:17 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 19:08:30 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_interface.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int		execute_command(char *const *args, char **env)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == -1)
		return (COULD_NOT_EXECUTE_COMMAND);
	if (child == 0)
	{
		status = execve(args[0], args, env);
		exit(COULD_NOT_EXECUTE_COMMAND);
	}
	else if (child > 0)
		waitpid(child, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		status = WSTOPSIG(status);
	return (status);
}
