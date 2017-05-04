/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:59:25 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 15:04:03 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char	*get_env_value(const char *key, char **env)
{
	int		key_length;
	size_t	index;

	index = 0;
	key_length = ft_strlen(key);
	while (environ[index] != NULL
			&& ft_strncmp(key, env[index], key_length) != 0)
		index++;
	return (env[index] + key_length + 1);
}

char		*get_env_entry(const char *key, char **env)
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

const char	*get_value(const char *env_entry)
{
	size_t	index;

	index = 0; while (env_entry[index] != '=')
		index++;
	return (env_entry + index + 1);
}
