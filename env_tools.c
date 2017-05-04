/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:17:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 15:03:08 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Entries are the whole string, key + value
*/

char		**copy_env(char * const * src, char **dst)
{
	size_t	index;

	index = 0;
	while (src[index] != NULL)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = NULL;
	return (dst);
}

static size_t		get_entry_value_len(const char *env_entry)
{
	while (*env_entry != '=')
		env_entry++;
	return (ft_strlen(env_entry + 1));
}

/*
** Require that the new value is shorter or equal to the previous one
*/

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

char		*replace_env(char *old_env_entry,
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

char		**add_new_entry(size_t index, const char *key,
		const char *value, char **env)
{
	char	**new_env;

	new_env = (malloc(sizeof(char*) * (index + 2)));
	if (new_env != NULL)
	{
		copy_env(env, new_env);
		new_env[index] = ft_strvajoin(3, key, "=", value);
		new_env[index + 1] = NULL;
		if (new_env[index] != NULL)
		{
			free(env);
			env = new_env;
		}
		else
		{
			free(new_env);
			env = NULL;
		}
	}
	return (env);
}

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
