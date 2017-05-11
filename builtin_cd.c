/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:13:46 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/11 19:08:46 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_interface.h"
#include "path_constants.h"
#include "libft.h"
#include <stddef.h>

/*
** Attempt to implement cd following the steps prescribed by POSIX at
** http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/

static char	*try_path(const char *dir_name, const char *path_name)
{
	char	*path_try;

	if (*path_name == '\0')
		path_name = ".";
	if (last_char_of(path_name) == '/')
		path_try = ft_strjoin(path_name, dir_name);
	else
		path_try = ft_strvajoin(3, path_name, "/", dir_name);
	if (!is_dir(path_try))
		ft_strdel(&path_try);
	return (path_try);
}

static char	*try_directory_paths(const char *dir_name, const char *cdpath)
{
	char	**paths;
	char	*path_try;
	size_t	index;

	index = 0;
	paths = ft_strsplit(cdpath, PATH_SEP);
	path_try = NULL;
	if (paths != NULL)
	{
		while (paths[index] != NULL && path_try == NULL)
		{
			path_try = try_path(dir_name, paths[index]);
			index++;
		}
	}
	ft_free_string_array(&paths);
	return (path_try);
}

static char	*produce_dir_operand(const char *directory, const t_shell *shell)
{
	char		*final_dir;
	const char	*home_dir;

	final_dir = NULL;
	home_dir = get_shell_env_value("HOME", shell);
	if (directory == NULL || ft_strcmp(directory, "-") == 0)
	{
		if (home_dir == NULL || ft_strcmp(home_dir, "") == 0)
			final_dir = NULL;
		else
			final_dir = ft_strdup(home_dir);
	}
	else
		final_dir = ft_strdup(directory);
	if (final_dir != NULL
			&& final_dir[0] != '/' && final_dir[0] != '.')
	{
		final_dir = try_directory_paths(final_dir,
				get_shell_env_value("CDPATH", shell));
	}
	return (final_dir);

}

void	delete_dot(char *path)
{
	size_t	index;
	char	*copy;

	index = 0;
	copy = path;
	while (path[index] != '\0')
	{
		while (((index == 0 && path == copy) || path[index - 1] == '/')
				&& ft_strncmp("./", path + index, 2) == 0)
			path += 2;
		if (path[index + 1] == '\0' && path[index] == '.'
				&& (index == 0 || path[index - 1] == '/'))
			path += 1;
		copy[index] = path[index];
		if (copy[index] == '\0')
			break ;
		index++;
	}
	copy[index] = '\0';
}

t_bool	valid_path_component(char *path, size_t	index)
{
	t_bool	path_is_valid;

	path[index] = '\0';
	path_is_valid = is_dir(path);
	path[index] = '/';
	return (path_is_valid);
}

char	*begin_next_component(char *path, size_t index)
{
	index += ft_strlen("..");
	if (path[index] != '\0')
		index++;
	return (path + index);
}

t_bool	should_delete_component(const char *path, size_t index, size_t index_preceding)
{
	return (ft_strnequ("..", path + index, ft_strlen(".."))
			&& (!ft_strnequ("..", path + index_preceding, ft_strlen("..")))
			&& !(path[index_preceding] == '/'));
}

char	*try_to_delete(char *const path)
{
	size_t	index;

	index = 0;
	if (!ft_strnequ("../", path, ft_strlen("../")))
	{
		while (path[index] != '/')
			index++;
		index++;
		if (ft_strnequ("..", path + index, ft_strlen(".."))
				&& (path[index + ft_strlen("..")] == '\0'
					|| path[index + ft_strlen("..")] == '/'))
		{
			if (valid_path_component(path, index - 1))
			{
				ft_strcpy(path, path + index +
						ft_strlen("..") +
						((path[index + ft_strlen("..")] == '/') ? 1 : 0));
			}
			else
				return (NULL);
		}
	}
	return (path);
}

char	*alt_delete_dot_dot(char *path)
{
	size_t	index;

	index = 0;
	if (try_to_delete(path) == NULL)
		return (NULL);
	while (path[index] != '\0')
	{
		if (path[index] == '/')
		{
			index++;
			if (try_to_delete(path + index) == NULL)
				return (NULL);
		}
		else
			index++;
	}
	return (path);
}
char	*delete_dot_dot(char *path)
{
	size_t	index;
	size_t	size_current;
	size_t	index_preceding;

	index = 0;
	index_preceding = 0;
	while (path[index] != '\0')
	{
		if (path[index] == '/')
		{
			index++;
			size_current = 0;
			while (path[index + size_current] != '/'
					&& path[index + size_current] != '\0')
				size_current++;
			if (should_delete_component(path, index, index_preceding))
			{
				if (valid_path_component(path, index - 1))
				{
					ft_strcpy(path + index_preceding,
							begin_next_component(path, index));
					index = index_preceding;
				}
				else
					return (NULL);
			}
			else
				index_preceding = index;
		}
		else
			index++;
	}
	return (path);
}

static void	convert_to_canonical(char *dir, const char *pwd)
{
	char	*new_dir;

	if (dir[0] != '/')
	{
		if (last_char_of(pwd) == '/')
			new_dir = ft_strjoin(pwd, dir);
		else
			new_dir = ft_strvajoin(3, pwd, "/", dir);
	}
}

static int	internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically)
{
	char	*directory;

	directory =
		produce_dir_operand(dir_operand,shell);
	if (directory == NULL)
		return (EXIT_FAILURE);
	else
	{
		if (dot_dot_logically)
		{
			convert_to_canonical(directory,
					get_shell_env_value("PWD", shell));
		}
	}
	return (0);
}

int	ft_cd(const char **argv, t_shell *shell_state)
{
	return (internal_cd(argv[1], shell_state, TRUE));
}
