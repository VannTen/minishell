/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:48:04 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 13:47:34 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "shell_interface.h"
#include "input_interface.h"
#include "error_interface.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	shell_loop(const char *argv[])
{
	t_input			input;
	t_exit_status	return_status;
	t_shell			*shell_state;
	extern char		**environ;

	shell_state = init_shell((const char**)environ, argv[0]);
	if (shell_state == NULL)
		return (SHELL_ENOMEM);
	while (!shall_exit(shell_state))
	{
		prompt_user(shell_state);
		input = get_input();
		if (has_input_error(input))
			break ;
		if (!input_is_empty(input))
		{
			return_status = search_and_execute_command(input, shell_state);
			set_exit_status(shell_state, return_status);
		}
		delete_input(&input);
	}
	return_status = deinit_shell(&shell_state);
	return (return_status);
}

int			main(int argc, const char *argv[])
{

	if (argc != 1)
	{
		ft_dprintf(STDERR_FILENO,
				"%s only works in interactive mode, cannot readscript\n",
				get_file_part(argv[0]));
		return (EXIT_FAILURE);;
	}
	else
		return (shell_loop(argv));
}
