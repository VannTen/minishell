/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 16:26:38 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 16:44:20 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_interface.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>

void	ft_shell_error(const char *shell_name, const char *utility,
		const char *arg, t_int_err err_code)
{
	int			precision_arg;
	int			precision_utility;
	int			precision_shell;
	const char	*err_mess[] = {
		"not enough arguments",
		"invalid argument",
		"command not found",
		"no such file or directory",
		"cannot execute"
	};

	precision_arg = arg != NULL ? -1 : 0;
	precision_utility = utility != NULL ? -1 : 0;
	precision_shell = shell_name != NULL ? -1 : 0;
	ft_dprintf(STDERR_FILENO,
			"%1$.*6$s%5$.*6$s%2$.*7$s%5$.*7$s%3$.*8$s%5$.*8$s%4$s\n",
			shell_name, utility, arg, err_mess[err_code],
			": ", precision_shell, precision_utility, precision_arg);
}
