/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonical_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 14:14:09 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/12 19:20:31 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool		valid_path_component(char *path, size_t index);

size_t		get_previous_component(char *path, size_t index_start)
{
	size_t	index_start_previous;
	size_t	index_end_previous;

	if (index_start == 0)
		return (0);
	index_end_previous = index_start - 1;
	while (path[index_end_previous] == '/' && index_end_previous != 0)
		index_end_previous--;
	index_start_previous = index_end_previous;
	while (path[index_start_previous] != '/' && index_start_previous != 0)
		index_start_previous--;
	if (path[index_start_previous] == '/')
		index_start_previous++;
	return (index_start_previous);
}

size_t	path_comp_len(const char *path_elem)
{
	size_t	index;

	index = 0;
	while (path_elem[index] != '\0' && path_elem[index] != '/')
		index++;
	return (index);
}

t_bool	path_component_are_equal(const char *path1, const char *path2)
{
	size_t	index;

	index = 0;
	while (path1[index] == path2[index]
			&& path1[index] != '\0' && path1[index] != '/'
			&& path2[index] != '\0' && path2[index] != '/')
		index++;
	return (path1[index] == path2[index]
			|| (path1[index] == '\0' && path2[index] == '/')
			|| (path2[index] == '\0' && path1[index] == '/'));
}

t_bool	is_root_component(const char *path, size_t index)
{
	while (index != 0 && path[index] == '/')
		index--;
	return (path[index] == '/');
}

t_bool	should_delete(const char *path, size_t index, size_t index_previous)
{
	return (index_previous != index
			&& !path_component_are_equal("..", path + index_previous)
			&& !is_root_component(path, index_previous));
}

size_t	advance_nbr_path_comp(const char *path, size_t nbr)
{
	size_t	index;

	index = 0;
	while (nbr != 0 && path[index] != '\0')
	{
		index += path_comp_len(path + index);
		while (path[index] == '/')
			index++;
		nbr--;
	}
	return (index);
}

size_t	advance_to_second_comp(const char *path)
{
	size_t	index;

	index = 0;
	while (path[index] != '\0' && path[index] != '/')
		index++;
	while (path[index] == '/')
		index++;
	return (index);
}

char	*delete_parent_ref(char *path)
{
	size_t	index;
	size_t	index_previous;

	index = advance_to_second_comp(path);
	while (path[index] != '\0')
	{
		if (path_component_are_equal("..", path + index))
		{
			index_previous = get_previous_component(path, index);
			if (should_delete(path, index, index_previous))
			{
				if (valid_path_component(path, index - 1))
				{
					ft_strcpy(path + index_previous,
							path + index + advance_nbr_path_comp(path + index, 1));
					index = index_previous;
					continue ;
				}
				else
					return (NULL);
			}
		}
		index += advance_nbr_path_comp(path + index, 1);
	}
	return (path);
}
