/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:38:04 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/23 18:40:13 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_INTERFACE_H
# define INPUT_INTERFACE_H
# include "libft.h"

typedef char**			t_input;

char		*get_raw_input(void);
t_input		parse_input(char *raw);
t_input		get_input(void);
void		delete_input(t_input *to_del);
t_bool		input_is_empty(t_input input);


#endif
