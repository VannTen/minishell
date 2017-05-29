/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:41:32 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 14:52:00 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"

t_bool		shall_exit(const t_shell *shell)
{
	return (shell->shall_exit);
}

int			get_exit_status(const t_shell *shell)
{
	return (shell->exit_status);
}

const char	*get_shell_name(const t_shell *shell)
{
	return (shell->name);
}
