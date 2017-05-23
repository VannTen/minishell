/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:48:04 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/23 18:53:53 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "shell_interface.h"
#include "input_interface.h"
#include "error_interface.h"
#include "libft.h"
#include <stddef.h>

int	main(void)
{
	t_input			input;
	t_exit_status	return_status;
	t_shell			*shell_state;
	extern char		**environ;

	shell_state = init_shell((const char**)environ);
	if (shell_state == NULL)
		return (SHELL_ENOMEM);
	while (!shall_exit(shell_state))
	{
		prompt_user(shell_state);
		input = get_input();
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
