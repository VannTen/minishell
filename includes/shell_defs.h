/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_defs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 13:31:37 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 14:47:49 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DEFS_H
# define SHELL_DEFS_H
# include "shell_interface.h"
# include "libft.h"

struct s_shell
{
	char	**env;
	char	**path;
	t_bool	persistent_path;
	t_bool	shall_exit;
	int		exit_status;
};

#endif
