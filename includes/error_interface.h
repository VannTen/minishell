/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:12:41 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 16:32:37 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_INTERFACE_H
# define ERROR_INTERFACE_H

typedef enum	e_exit_status
{
	NO_ERROR,
	SHELL_ENOMEM,
	COULD_NOT_EXECUTE_COMMAND = 126,
	COMMAND_NOT_FOUND = 127,
	EXIT_STATUS_OUT_OF_RANGE = 255,
}				t_exit_status;

typedef	enum	e_inter_err
{
	NOT_ENOUGH_ARGS,
	BAD_ARG,
	COM_NOT_FOUND,
	NO_FILE,
	CANNOT_EXE
}				t_int_err;

void	ft_shell_error(const char *shell_name, const char *utility,
		const char *arg, t_int_err err_code);

#endif
