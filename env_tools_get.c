/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:59:25 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/15 13:35:17 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char		*get_env_entry(const char *key, char **env)
{
	int		key_length;
	size_t	index;

	index = 0;
	key_length = ft_strlen(key);
	while (env[index] != NULL
			&& ft_strncmp(key, env[index], key_length) != 0)
		index++;
	return (env[index]);
}

const char	*get_env_value(const char *key, char **env)
{
	size_t		index;
	const char	*entry;
	const char	*value;

	index = 0;
	entry = get_env_entry(key, env);
	value = entry + (entry == NULL ? 0 : ft_strlen(key) + 1);

	return (value);
}

const char	*get_value(const char *env_entry)
{
	size_t	index;

	index = 0; while (env_entry[index] != '=')
		index++;
	return (env_entry + index + 1);
}
