/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:40:29 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/25 14:43:31 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_defs.h"

t_bool	has_input_error(t_input input)
{
	return (input == NULL);
}

t_bool	input_is_empty(t_input input)
{
	return (input == NULL || input[0] == NULL);
}
