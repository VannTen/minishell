/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:09:07 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/30 17:08:09 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "libft.h"
#include <unistd.h>

void	prompt_user(t_shell *shell)
{
	ft_printf("(last : %d)\n$>",
			get_exit_status(shell));
}

void	shell_error(const char *shell_name, enum e_err_code error_code,
		const char *arg)
{
	const char	*error_mess[] = {
		"command not found",
		"Permission denied",
		"No such file or directory"
	};

	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", shell_name, arg,
			error_mess[error_code]);
}
