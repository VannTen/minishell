/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_intern_operand.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:48:34 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/19 18:56:24 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd_defs.h"
#include "path_constants.h"

static char	*try_path(const char *dir_name, const char *path_name)
{
	char	*path_try;

	if (path_name == NULL || *path_name == '\0')
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
	else
		path_try = try_path(dir_name, NULL);
	ft_free_string_array(&paths);
	if (path_try == NULL)
		path_try = ft_strdup(dir_name);
	return (path_try);
}

char		*produce_dir_operand(const char *directory, const t_shell *shell)
{
	char		*final_dir;
	const char	*home_dir;

	final_dir = NULL;
	home_dir = get_shell_env_value("HOME", shell);
	if (directory == NULL || ft_strcmp(directory, "-") == 0)
	{
		if (home_dir == NULL || ft_strcmp(home_dir, "") == 0)
			directory = NULL;
		else
			directory = home_dir;
	}
	if (directory != NULL
			&& directory[0] != '/' && directory[0] != '.')
	{
		final_dir = try_directory_paths(directory,
				get_shell_env_value("CDPATH", shell));
	}
	else
		final_dir = ft_strdup(directory);
	return (final_dir);
}
