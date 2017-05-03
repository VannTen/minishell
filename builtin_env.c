/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:33:48 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/03 16:44:40 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_interface.h"
#include "builtin_env_defs.h"
#include "builtins_defs.h"

static int	apply_i(void *v_param)
{
	t_env_param	*param;

	param = v_param;
	param->options[IGNORE_ENV] = TRUE;
	return (OPT_SUCCESS);
}

static int	apply_v(void *v_param)
{
	t_env_param	*param;

	param = v_param;
	param->options[VERBOSE] = TRUE;
	return (OPT_SUCCESS);
}

static int	apply_u(void *v_param, const char *arg)
{
	t_env_param	*param;
	char		*key;

	param = v_param;
	key = get_key(arg);
	param->env = ft_removeenv(key, param->env);
	ft_strdel(&key);
	return (OPT_SUCCESS);
}

static int	apply_P(void *v_param, const char *arg)
{
	t_env_param	*param;
	char		*key;

	param = v_param;
	key = get_key(arg);
	param->env = ft_removeenv(key, param->env);
	ft_strdel(&key);
	return (OPT_SUCCESS);
}

static int	apply_S(void *v_param, const char *arg)
{
	t_env_param	*param;
	char		*key;

	param = v_param;
	key = get_key(arg);
	param->env = ft_removeenv(key, param->env);
	ft_strdel(&key);
	return (OPT_SUCCESS);
}

static t_bool	opt_is_valid(int opt_return_status)
{
	return (opt_return_status == OPT_SUCCESS);
}

static void		env_usage(const char *prog_name)
{
	ft_dprintf(STDERR_FILENO, "usage: %s "
			"[-" ENV_OPT_STRING "] [-P utilpath] [-S string] [-u name]"
			"\n[name=value ...] [utility [argument ...]]",
			prog_name);
}

static	t_env_param *default_param(char **env)
{
	static t_env_param	params;
	static t_bool		options[OPT_NBR + 1];
	size_t				index;

	index = 0;
	while (index < OPT_NBR)
	{
		options[index] = FALSE;
		index++;
	}
	params.options = options;
	params.path_string = NULL;
	params.env = ft_string_array_dup((const char**)env);
	if (params.env == NULL)
		return (NULL);
	return (&params);
}

static int	apply_options(const char **argv, t_env_param *param)
{
	const t_apply_opt_param	param_opt[OPT_ARG_NBR] = {
		apply_P,
		apply_S,
		apply_u
	};
	const t_apply_opt		apply_opt[OPT_NBR] = {
		apply_i,
		apply_v
	};
	int						options_return;
	t_synopsis				*synopsis;

	synopsis = init_synopsis(ENV_OPT_STRING, apply_opt,
			ENV_OPT_ARG_STRING, param_opt);
	add_opt_validator(synopsis, opt_is_valid);
	add_usage(synopsis, env_usage);
	options_return = apply_cmdline_opt(synopsis, argv, param);
	return (options_return);
}

int	ft_env(const char **argv, t_shell *shell_state)
{
	int			option_number;
	int			return_status;
	int			index;
	char *const	*path;
	t_env_param	*param;

	param = default_param(get_env(shell_state));
	option_number = apply_options(argv, param);
	return_status = 0;
	index = option_number;
	while (is_valid_setenv(argv[index]))
	{
		param->env = ft_setenv_intern(param->env, argv[index]);
		index++;
	}
	if (argv[index] != NULL)
	{
		path = ft_strsplit(param->path_string == NULL ?
				get_value("PATH") : param->path_string,
				':');
		return_status = exec_any(argv[option_number],
				argv + index, param->env);
	}
	else
		ft_print_string_array(param->env, '\n');
	ft_free_string_array(&param->env);
	return (return_status);
}
