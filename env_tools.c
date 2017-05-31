/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:17:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 18:10:48 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	is_valid_setenv(const char *arg)
{
	size_t	index;

	index = 0;
	if (arg == NULL)
		return (FALSE);
	while (arg[index] != '\0' && arg[index] != '=')
		index++;
	if (arg[index] == '=')
		return (TRUE);
	else
		return (FALSE);
}
