/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:57:38 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 15:03:03 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
