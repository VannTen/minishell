/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:59:25 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 16:04:22 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_defs.h"
#include "libft.h"
#include <stddef.h>

char		*get_env_entry(const char *key, char **env)
{
	int		key_length;
	size_t	index;

	index = 0;
	key_length = ft_strlen(key);
	while (env[index] != NULL && !key_are_equal(key, env[index]))
		index++;
	return (env[index]);
}

const char	*get_env_value(const char *key, char **env)
{
	const char	*entry;
	const char	*value;

	entry = get_env_entry(key, env);
	value = entry + (entry == NULL ? 0 : ft_strlen(key) + 1);
	return (value);
}

const char	*get_value(const char *env_entry)
{
	size_t	index;

	index = 0;
	while (env_entry[index] != '=')
		index++;
	return (env_entry + index + 1);
}
