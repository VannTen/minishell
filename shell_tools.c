/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:09:07 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/26 16:05:38 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "libft.h"

void	prompt_user(const t_shell *shell)
{
	ft_printf("(last : %d)\n(PWD: %s)\n(OLDPWD: %s)\n$>",
			get_exit_status(shell),
			get_shell_env_value("PWD", shell),
			get_shell_env_value("OLDPWD", shell));
}
