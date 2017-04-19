/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:17:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 15:07:58 by mgautier         ###   ########.fr       */
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

/*
** Entries are the whole string, key + value
*/

char		*get_env_entry(const char *key)
{
	int		key_length;
	size_t	index;

	index = 0;
	key_length = ft_strlen(key);
	while (environ[index] != NULL
			&& ft_strncmp(key, environ[index], key_length) != 0)
		index++;
	return (environ[index]);
}

char		*get_key(const char *env_entry)
{
	size_t	index;
	char	*key;

	index = 0;
	key = NULL;
	while (env_entry[index] != '=')
		index++;
	if (env_entry[index] != '\0')
		key = ft_strndup(env_entry, index);
	return (key);
}
