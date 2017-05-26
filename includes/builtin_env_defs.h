/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_defs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:36:12 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/26 16:40:48 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_DEFS_H
# define BUILTIN_ENV_DEFS_H
# include "builtin_env_interface.h"
# include "shell_interface.h"
# include "libft.h"

enum	e_env_opt_return_status
{
	OPT_SUCCESS,
	OPT_FAILURE
};

enum	e_env_flags
{
	VERBOSE,
	FLAGS_NBR
};

typedef struct s_env_param	t_env_param;
struct		s_env_param
{
	t_bool		flags[FLAGS_NBR];
	const char	*prog_name;
	t_shell		*sub_shell;
};

/*
** Internal functions
** Implementation file : builtin_env_intern.c
*/

int			apply_options(const char **argv,
		t_env_param *param);
t_env_param	*init_param(const char **env);
void		deinit_param(t_env_param **params);

#endif
