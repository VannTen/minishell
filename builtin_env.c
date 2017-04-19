/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:33:48 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 19:50:05 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_env_defs.h"
#include "builtins_defs.h"
#include "libft.h"

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

/*
static void	apply_u(char *arg, void *v_param)
{
	t_env_param	*param;

	param = v_param;
	intern_unset_env(arg, param->env);
}
*/

int	ft_env(char	**argv, t_shell *shell_state)
{
	char		**env_cpy;
	int			option_number;
	int			option_param_nbr;
	int			total_opt;
	int			return_status;
	t_env_param	*param;

	param = default_param(argv, &option_number);
	return_status = 0;
	if (param->options[IGNORE_ENV])
		env_cpy = ft_string_array_dup((const char**)get_env(shell_state));
	else
		env_cpy = NULL;
	//option_param_nbr = apply_parameter_options(param, argv + option_number);
	option_param_nbr = 0;
	total_opt = option_param_nbr + option_number;
/*
	if (argv[total_opt] != NULL)
		return_status = exec_any(argv[total_opt], argv + total_opt, env_cpy);
	else*/
		ft_print_string_array(env_cpy, '\n');
	ft_free_string_array(&env_cpy);
	return (return_status);
}
