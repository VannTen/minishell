/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:17:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/18 17:33:49 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

extern char	**environ;

const char	*get_env_value(const char *key)
{
	int		key_length;
	size_t	index;

	index = 0;
	key_length = ft_strlen(key);
	while (environ[index] != NULL
			&& ft_strncmp(key, environ[index], key_length) != 0)
			index++;
	return (environ[index] + key_length + 1);
}
