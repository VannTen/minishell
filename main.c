/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:48:04 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/17 16:56:20 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>

char	*get_raw_input(void)
{
	char *input;

	get_next_line(STDIN_FILENO, &input);
	return (input);
}

t_input	parse_input(char *raw)
{
	char **commands_and_args;

	commands_and_args = ft_strsplit(raw, ' ');
	ft_strdel(&raw);
	return (commands_and_args);
}

int		exec_input(t_input com_and_args)
{
	pid_t	child_process;
	int		stat_loc;

	stat_loc = 0;
	child_process = fork();
	if (child_process == 0)
		execve(com_and_args[0], com_and_args, NULL);
	else if (child_process > 0)
	{
		ft_free_string_array(&com_and_args);
		wait(&stat_loc);
	}
	return (stat_loc);
}

int main(void)
{
	char	*raw_input;
	t_input	input;
	int		return_status;

	while (1)
	{
		ft_printf(PROMPT);
		raw_input = get_raw_input();
		input = parse_input(raw_input);
		return_status = exec_input(input);
		ft_printf("Command return : %d\n", return_status);
	}
}
