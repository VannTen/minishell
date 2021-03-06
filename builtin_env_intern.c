/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_intern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:02:35 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 14:22:34 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_env_options.h"
#include "builtin_env_defs.h"
#include <stdlib.h>
#include <unistd.h>

static t_bool	opt_is_valid(int opt_return_status)
{
	return (opt_return_status == OPT_SUCCESS);
}

static void		env_usage(const char *prog_name)
{
	ft_dprintf(STDERR_FILENO, "usage: %s "
			"[-" ENV_OPT_STRING "] [-P utilpath] [-S string] [-u name]"
			"\n[name=value ...] [utility [argument ...]]\n",
			prog_name);
}

void			deinit_param(t_env_param **params)
{
	t_env_param	*to_del;

	to_del = *params;
	if (to_del != NULL)
	{
		deinit_shell(&to_del->sub_shell);
		free(to_del);
		*params = NULL;
	}
}

t_env_param		*init_param(char const *const *env)
{
	t_env_param	*params;
	size_t		index;

	params = malloc(sizeof(t_env_param));
	if (params != NULL)
	{
		index = 0;
		while (index < FLAGS_NBR)
		{
			params->flags[index] = FALSE;
			index++;
		}
		params->sub_shell = init_shell(env, "env");
		if (params->sub_shell == NULL)
			deinit_param(&params);
	}
	return (params);
}

int				apply_options(char const *const *argv, t_env_param *param)
{
	const t_apply_opt_param	param_opt[] = {
		apply_big_p,
		apply_big_s,
		apply_u
	};
	const t_apply_opt		apply_opt[] = {
		apply_i,
		apply_v
	};
	int						options_return;
	t_synopsis				*synopsis;

	synopsis = init_synopsis(ENV_OPT_STRING, apply_opt,
			ENV_OPT_ARG_STRING, param_opt);
	if (synopsis != NULL)
	{
		add_opt_validator(synopsis, opt_is_valid);
		add_usage(synopsis, env_usage, argv[0]);
		options_return = apply_cmdline_opt(synopsis, argv, param);
		deinit_synopsis(&synopsis);
	}
	else
		return (-1);
	return (options_return);
}
