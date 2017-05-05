/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:20 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 14:46:23 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"

void	will_exit(t_shell *shell)
{
	shell->shall_exit = TRUE;
}

void	set_exit_status(t_shell *shell, int status)
{
	shell->exit_status = status;
}
