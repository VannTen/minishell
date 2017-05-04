/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:48:04 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 15:44:03 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "shell_interface.h"
#include "error_interface.h"
#include "libft.h"
#include <stddef.h>

extern char	**environ;

char		*get_raw_input(void)
{
	char *input;

	get_next_line(STDIN_FILENO, &input);
	return (input);
}

t_input		parse_input(char *raw)
{
	char **commands_and_args;

	commands_and_args = ft_strsplit(raw, ' ');
	return (commands_and_args);
}

t_input		get_input(void)
{
	char	*raw_input;
	t_input	input;

	raw_input = get_raw_input();
	input = parse_input(raw_input);
	ft_strdel(&raw_input);
	return (input);
}

void		delete_input(t_input *to_del)
{
	ft_free_string_array(to_del);
	*to_del = NULL;
}

int			 main(void)
{
	t_input	input;
	int		return_status;
	t_shell	*shell_state;

	shell_state = init_shell((const char**)environ);
	if (shell_state == NULL)
		return (SHELL_ENOMEM);
	while (1)
	{
		ft_printf(PROMPT);
		input = get_input();
		return_status = exec_input(input, shell_state);
		delete_input(&input);
		ft_printf("Command return : %d\n", return_status);
	}
}
