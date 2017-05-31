/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:03:17 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 14:05:13 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_interface.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

static void	signal_error(int signal_number)
{
	const char	*signal_str[] = {
		"HUP", "INT", "QUIT", "ILL", "TRAP", "TABRT", "EMT", "FPE", "KILL",
		"BUS", "SEGV", "SYS", "PIPE", "ALRM", "TERM", "URG", "STOP", "STP",
		"CONT", "CHLD", "TTIN", "TTOU", "IO", "XCPU", "VTALRM", "PROF",
		"WINCH", "INFO", "USR1", "USR2"};

	if (signal_number >= 1 && signal_number <= 31)
		ft_dprintf(STDERR_FILENO, "Process received signal SIG%s\n",
				signal_str[signal_number - 1]);
}

int			execute_command(const char *command_path,
		char const *const *args, char const *const *env)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == -1)
		return (COULD_NOT_EXECUTE_COMMAND);
	if (child == 0)
	{
		status = execve(command_path, (char *const *)args, (char *const *)env);
		exit(COULD_NOT_EXECUTE_COMMAND);
	}
	else if (child > 0)
		waitpid(child, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		status = 128 + WTERMSIG(status);
		signal_error(WTERMSIG(status));
	}
	else if (WIFSTOPPED(status))
		status = WSTOPSIG(status);
	return (status);
}
