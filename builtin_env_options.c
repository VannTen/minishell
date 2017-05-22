/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 13:43:39 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/19 19:03:24 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_env_defs.h"
#include "shell_interface.h"
#include <unistd.h>

int	apply_i(void *v_param)
{
	t_env_param	*param;

	param = v_param;
	if (param->flags[VERBOSE])
		ft_dprintf(STDERR_FILENO, "#env clearing environ\n");
	empty_shell_env(param->sub_shell);
	return (OPT_SUCCESS);
}

int	apply_v(void *v_param)
{
	t_env_param	*param;

	param = v_param;
	param->flags[VERBOSE] = TRUE;
	return (OPT_SUCCESS);
}

int	apply_u(void *v_param, const char *arg)
{
	t_env_param	*param;

	param = v_param;
	if (param->flags[VERBOSE])
		ft_dprintf(STDERR_FILENO, "#env unset: %s\n", arg);
	unset_env(param->sub_shell, arg);
	return (OPT_SUCCESS);
}

int	apply_big_p(void *v_param, const char *arg)
{
	t_env_param	*param;

	param = v_param;
	set_path(param->sub_shell, arg);
	return (OPT_SUCCESS);
}

int	apply_big_s(void *v_param, const char *arg)
{
	(void)v_param;
	(void)arg;
	return (OPT_SUCCESS);
}
