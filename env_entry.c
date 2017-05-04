/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:57:38 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 15:16:10 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char		*get_key(const char *env_entry)
{
	size_t	index;
	char	*key;

	index = 0;
	key = NULL;
	while (env_entry[index] != '=' && env_entry != '\0')
		index++;
	if (env_entry[index] != '\0')
		key = ft_strndup(env_entry, index);
	return (key);
}

t_bool		key_are_equal(const char *searched_key, const char *env_entry)
{
	size_t	index;

	index = 0;
	while (searched_key[index] == env_entry[index]
			&& searched_key[index] != '\0'
			&& env_entry[index] != '\0')
		index++;
	if (env_entry[index] == '=' && searched_key[index] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

static size_t		get_entry_value_len(const char *env_entry)
{
	while (*env_entry != '=')
		env_entry++;
	return (ft_strlen(env_entry + 1));
}

static void			put_entry_value(char *env_entry, const char *new_value)
{
	while (*env_entry != '=')
		env_entry++;
	env_entry++;
	while (*new_value != '\0')
	{
		*env_entry = *new_value;
		env_entry++;
		new_value++;
	}
	*env_entry = '\0';
}

char		*replace_env_entry(char *old_env_entry,
		const char *key, const char *new_value)
{
	size_t	old_value_len;
	size_t	new_value_len;
	char	*new_entry;

	old_value_len = get_entry_value_len(old_env_entry);
	new_value_len = ft_strlen(new_value);
	if (new_value_len > old_value_len)
	{
		new_entry = ft_strvajoin(3, key, "=", new_value);
		if (old_env_entry != NULL)
		{
			ft_strdel(&old_env_entry);
			old_env_entry = new_entry;
		}
		else
			old_env_entry = NULL;
	}
	else
		put_entry_value(old_env_entry, new_value);
	return (old_env_entry);
}
