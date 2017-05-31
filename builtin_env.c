/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:33:48 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 16:41:50 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_interface.h"
#include "builtin_env_defs.h"
#include "builtins_defs.h"
#include "shell_interface.h"
#include "error_interface.h"

static int	intern_env(char const *const *argv, const t_env_param *param,
		int index)
{
	while (set_env(param->sub_shell, argv[index]) == BUILTIN_EXIT_SUCCESS)
		index++;
	if (argv[index] != NULL)
		return (search_external_command(
					argv + index, param->sub_shell));
	else
	{
		ft_print_string_array((const char**)get_env(param->sub_shell), '\n');
		ft_putchar('\n');
		return (BUILTIN_EXIT_SUCCESS);
	}
}

int			ft_env(char const *const *argv, t_shell *shell)
{
	int			option_number;
	int			return_status;
	t_env_param	*param;

	param = init_param(get_env(shell));
	return_status = BUILTIN_EXIT_FAILURE;
	if (param != NULL)
	{
		option_number = apply_options(argv, param);
		if (option_number != USAGE_ERROR)
			return_status = intern_env(argv, param, option_number);
		deinit_param(&param);
	}
	if (return_status == COMMAND_NOT_FOUND)
		ft_shell_error(get_shell_name(shell), "env", argv[1], COM_NOT_FOUND);
	else if (return_status == COULD_NOT_EXECUTE_COMMAND)
		ft_shell_error(get_shell_name(shell), "env", argv[1], CANNOT_EXE);
	return (return_status);
}
