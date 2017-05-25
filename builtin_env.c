/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:33:48 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/25 15:35:49 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_interface.h"
#include "builtin_env_defs.h"
#include "builtins_defs.h"
#include "shell_interface.h"

int	ft_env(const char **argv, t_shell *shell_state)
{
	int			option_number;
	int			return_status;
	int			index;
	t_env_param	*param;

	param = init_param((const char **)get_env(shell_state));
	if (param != NULL)
	{
		option_number = apply_options(argv, param);
		return_status = 0;
		index = option_number;
		while (set_env(param->sub_shell, argv[index]) == BUILTIN_EXIT_SUCCESS)
			index++;
		if (argv[index] != NULL)
		{
			return_status = search_and_execute_command(
					(char**)argv + index,
					param->sub_shell);
		}
		else
			ft_print_string_array((const char**)get_env(param->sub_shell), '\n');
		deinit_param(&param);
		return (return_status);
	}
	return (BUILTIN_EXIT_FAILURE);
}
