/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_defs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:31:37 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 19:17:02 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DEFS_H
# define SHELL_DEFS_H
# include "shell_interface.h"
# include "libft.h"

struct s_shell
{
	char	**env;
	t_bool	env_has_changed_since_path_update;
	char	**path;
};

#endif
