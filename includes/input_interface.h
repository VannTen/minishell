/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:38:04 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/26 16:36:36 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_INTERFACE_H
# define INPUT_INTERFACE_H
# include "libft.h"

typedef char**			t_input;

/*
** Get and parse input
** Implementation file : input.c
*/

char		*get_raw_input(void);
t_input		parse_input(char *raw);
t_input		get_input(void);
void		delete_input(t_input *to_del);

/*
** Input errors
** Implementation file : input_error.c
*/

t_bool		input_is_empty(t_input input);
t_bool		has_input_error(t_input input);

#endif
