/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:33:48 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/26 18:35:52 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_interface.h"
#include "builtin_env_defs.h"
#include "builtins_defs.h"
#include "shell_interface.h"

static int	intern_env(const char **argv, const t_env_param *param, int index)
{
	while (set_env(param->sub_shell, argv[index]) == BUILTIN_EXIT_SUCCESS)
		index++;
	if (argv[index] != NULL)
		return (search_and_exe_external_command(
					(char**)argv + index, param->sub_shell));
	else
	{
		ft_print_string_array((const char**)get_env(param->sub_shell),
				'\n');
		return (BUILTIN_EXIT_SUCCESS);
	}
}

int			ft_env(const char **argv, t_shell *shell_state)
{
	int			option_number;
	int			return_status;
	t_env_param	*param;

	param = init_param((const char **)get_env(shell_state));
	return_status = BUILTIN_EXIT_FAILURE;
	if (param != NULL)
	{
		option_number = apply_options(argv, param);
		if (option_number != USAGE_ERROR)
			return_status = intern_env(argv, param, option_number);
		deinit_param(&param);
	}
	return (return_status);
}
