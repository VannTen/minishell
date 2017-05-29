/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:43:20 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 12:02:44 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "libft.h"

void	will_exit(t_shell *shell)
{
	shell->shall_exit = TRUE;
}

void	set_exit_status(t_shell *shell, int status)
{
	shell->exit_status = status;
}

void	set_shell_name(t_shell *shell, const char *prog_path)
{
	shell->name = get_file_part(prog_path);
}
