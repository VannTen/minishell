/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:12:41 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 16:01:24 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_INTERFACE_H
# define ERROR_INTERFACE_H

typedef enum	e_exit_status
{
	SHELL_ENOMEM,
	COULD_NOT_EXECUTE_COMMAND = 126,
	COMMAND_NOT_FOUND = 127
}				t_exit_status;

#endif
