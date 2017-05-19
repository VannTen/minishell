/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_defs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:15:30 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/19 18:54:20 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_DEFS_H
# define BUILTIN_CD_DEFS_H
# include "shell_interface.h"
# include "libft.h"

typedef struct s_cd_param	t_cd_param;

struct s_cd_param
{
	t_bool	dot_dot_logically;
};

/*
** Cd internal functions
** Implementation files : builtin_cd_intern.c & builtin_cd_intern_operand.c
*/

int		internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically);
char	*produce_dir_operand(const char *directory, const t_shell *shell);
#endif
