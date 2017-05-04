/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:17:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 11:35:29 by mgautier         ###   ########.fr       */
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
	while (env_entry[index] != '=' && env_entry != '\0')
		index++;
	if (env_entry[index] != '\0')
		key = ft_strndup(env_entry, index);
	return (key);
}

const char	*get_value(const char *env_entry)
{
	size_t	index;

	index = 0;
	while (env_entry[index] != '=')
		index++;
	return (env_entry + index + 1);
}

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

static size_t		get_entry_value_len(char *env_entry)
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

/*
char		*add_new_env_entry(const char *key, const char *value,
size_t size, char **env)
{
}
*/

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

char		**ft_putenv(const char *key, const char *value, char **env)
{
	size_t	index;
	char	*new_entry;

	index = 0;
	while (env[index] != NULL && !key_are_equal(key, env[index]))
		index++;
	if (env[index] == NULL)
		env = add_new_entry(index, key, value, env);
	else
	{
		new_entry = replace_env(env[index], key, value);
		if (new_entry != NULL)
			env[index] = new_entry;
		else
			env = NULL;
	}
	return (env);
}

char	**empty_env(char **env)
{
	char	**new_env;

	ft_free_string_array(&env);
	new_env = malloc(sizeof(char*) * 1);
	if (new_env != NULL)
		new_env[0] = NULL;
	return (new_env);
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

char	**ft_removeenv(const char *key, char **env)
{
	size_t	index;

	index = 0;
	while (env[index] != NULL)
	{
		if (key_are_equal(key, env[index]))
			break ;
		index++;
	}
	if (env[index] != NULL)
	{
		while (env[index] != NULL)
		{
			env[index] = env[index + 1];
			index++;
		}
	}
	return (env);
}

char	**ft_setenv_intern(char **env, const char *setenv)
{
	char	*key;
	const char	*value;
	char		**new_env;

	key = get_key(setenv);
	value = get_value(setenv);
	new_env = ft_putenv(key, value, env);
	ft_strdel(&key);
	return (new_env);
}
