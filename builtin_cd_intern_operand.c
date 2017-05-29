/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_intern_operand.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:48:34 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 16:08:26 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd_defs.h"
#include "path_constants.h"
#include "libft.h"
#include <unistd.h>

static char			*try_path(const char *dir_name, const char *path_name)
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

static char			*try_directory_paths(const char *dir_name,
		const char *cdpath, t_bool *write_new_dir)
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
	else
		*write_new_dir = TRUE;
	return (path_try);
}

static const char	*get_env_dir_value(const char *key, const t_shell *shell)
{
	const char	*value;

	value = get_shell_env_value(key, shell);
	if (value == NULL || ft_strequ(value, ""))
		return (NULL);
	else
		return (value);
}

char				*produce_dir_operand(const char *directory,
		const t_shell *shell, t_bool *write_new_dir)
{
	char		*final_dir;
	const char	*ref_to;

	final_dir = NULL;
	ref_to = NULL;
	if (directory == NULL)
		ref_to = "HOME";
	else if (ft_strequ(directory, "-"))
	{
		ref_to = "OLDPWD";
		*write_new_dir = TRUE;
	}
	if (ref_to != NULL)
	{
		directory = get_env_dir_value(ref_to, shell);
		if (directory == NULL)
			ft_dprintf(STDERR_FILENO, "%s: cd: %s not set\n",
					get_shell_name(shell), ref_to);
	}
	if (directory != NULL && directory[0] != '/' && directory[0] != '.')
		final_dir = try_directory_paths(directory,
				get_shell_env_value("CDPATH", shell), write_new_dir);
	else
		final_dir = ft_strdup(directory);
	return (final_dir);
}
