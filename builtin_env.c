/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:33:48 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/02 10:10:44 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_interface.h"
#include "builtin_env_defs.h"
#include "builtins_defs.h"

static void	apply_i(void *v_param)
{
	t_env_param	*param;

	param = v_param;
	param->options[IGNORE_ENV] = TRUE;
}

static void	apply_v(void *v_param)
{
	t_env_param	*param;

	param = v_param;
	param->options[VERBOSE] = TRUE;
}

static	t_env_param *default_param(char **argv, int *opt_nbr)
{
	static t_env_param	params;
	static t_bool		options[OPT_NBR + 1];
	size_t				index;
	const t_apply_opt	apply_opt[OPT_NBR] = {
		apply_i,
		apply_v
	};

	index = 0;
	while (index < OPT_NBR)
		options[index] = FALSE;
	params.options = options;
	*opt_nbr =
		apply_cmdline_opt(ENV_SYNOPSIS, (const char**)argv, (void*)&params, apply_opt);
	return (&params);
}

static void	apply_u(void *v_param, const char *arg)
{
	t_env_param	*param;
	char		*key;

	param = v_param;
	key = get_key(arg);
	param->env = ft_removeenv(key, param->env);
	ft_strdel(&key);
}

static void	apply_P(void *v_param, const char *arg)
{
	t_env_param	*param;
	char		*key;

	param = v_param;
	key = get_key(arg);
	param->env = ft_removeenv(key, param->env);
	ft_strdel(&key);
}

static void	apply_S(void *v_param, const char *arg)
{
	t_env_param	*param;
	char		*key;

	param = v_param;
	key = get_key(arg);
	param->env = ft_removeenv(key, param->env);
	ft_strdel(&key);
}

static int	param_options(char	**argv, t_env_param *param)
{
	const t_apply_opt_param	param_opt[OPT_ARG_NBR] = {
		apply_P,
		apply_S,
		apply_u
	};
	size_t					index;

	index = 0;
	return (apply_parameters_options(
				ENV_ARG_SYNOPSIS, (const char**)argv, param, param_opt));
}

int	ft_env(char	**argv, t_shell *shell_state)
{
	int			option_number;
	int			option_param_nbr;
	int			total_opt;
	int			return_status;
	t_env_param	*param;

	param = default_param(argv, &option_number);
	return_status = 0;
	if (param->options[IGNORE_ENV])
		param->env = NULL;
	else
		param->env = ft_string_array_dup((const char**)get_env(shell_state));
	option_param_nbr = param_options(argv + option_number, param);
	total_opt = option_param_nbr + option_number;
/*
	if (argv[total_opt] != NULL)
		return_status = exec_any(argv[total_opt], argv + total_opt, env_cpy);
	else*/
		ft_print_string_array(param->env, '\n');
	ft_free_string_array(&param->env);
	return (return_status);
}
