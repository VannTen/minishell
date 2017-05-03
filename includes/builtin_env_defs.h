/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_defs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:36:12 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/03 15:59:13 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_DEFS_H
# define BUILTIN_ENV_DEFS_H
# include "builtin_env_interface.h"
# include "libft.h"

enum	e_env_opt_return_status
{
	OPT_SUCCESS,
	OPT_FAILURE
};

typedef struct s_env_param t_env_param;
struct	s_env_param
{
	t_bool		*options;
	const char	*prog_name;
	char		**env;
	char		*path_string;
};

#endif
