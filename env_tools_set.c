/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:00:48 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 11:28:30 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_interface.h"
#include "libft.h"
#include <stdlib.h>

static char	**add_new_entry(size_t index, const char *key,
		const char *value, char **env)
{
	char	**new_env;

	new_env = malloc(sizeof(char*) * (index + 2));
	if (new_env != NULL)
	{
		ft_str_array_cpy(env, new_env);
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
			new_env = NULL;
		}
	}
	return (new_env);
}

char		**ft_putenv(const char *key, const char *value, char **env)
{
	size_t	index;
	char	*new_entry;
	char	**new_env;

	index = 0;
	while (env[index] != NULL && !key_are_equal(key, env[index]))
		index++;
	if (env[index] == NULL)
	{
		new_env = add_new_entry(index, key, value, env);
		if (new_env == NULL)
			env = NULL;
		else
			env = new_env;
	}
	else
	{
		new_entry = replace_env_entry(env[index], key, value);
		if (new_entry != NULL)
			env[index] = new_entry;
		else
			env = NULL;
	}
	return (env);
}

char		**ft_removeenv(const char *key, char **env)
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
		ft_strdel(env + index);
		env[index] = env[index + 1];
		index++;
		while (env[index] != NULL)
		{
			env[index] = env[index + 1];
			index++;
		}
	}
	return (env);
}

char		**empty_env(char **env)
{
	char	**new_env;

	ft_free_string_array(&env);
	new_env = malloc(sizeof(char*) * 1);
	if (new_env != NULL)
		new_env[0] = NULL;
	return (new_env);
}
