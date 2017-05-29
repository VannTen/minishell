/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 11:46:35 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 13:40:16 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_defs.h"
#include "shell_interface.h"
#include "error_interface.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>

static int	intern_exit(const char **argv, t_shell *shell)
{
	int exit_status;

	if (string_is_digit(argv[1]))
		exit_status = ft_strict_atoi(argv[1]);
	else
	{
		exit_status = EXIT_STATUS_OUT_OF_RANGE;
		ft_dprintf(STDERR_FILENO, "%s: %s: %s: numeric_argument_required\n",
				get_shell_name(shell), "exit", argv[1]);
	}
	will_exit(shell);
	return (exit_status);
}

int			ft_exit(const char **argv, t_shell *shell)
{
	int		exit_status;
	size_t	arg_count;

	arg_count = ft_string_array_count(argv);
	if (arg_count == 2)
		exit_status = intern_exit(argv, shell);
	else if (arg_count < 2)
	{
		exit_status = BUILTIN_EXIT_FAILURE;
		ft_dprintf(STDERR_FILENO,
				"%s: %s: too many arguments", get_shell_name(shell), "exit");
	}
	else
	{
		exit_status = BUILTIN_EXIT_SUCCESS;
		will_exit(shell);
	}
	return (exit_status);
}
