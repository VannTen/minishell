/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:13:46 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/15 12:23:55 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd_defs.h"
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

static char	*get_add_pwd(const char *dir, const char *pwd)
{
	char	*new_dir;

	if (last_char_of(pwd) == '/')
		new_dir = ft_strjoin(pwd, dir);
	else
		new_dir = ft_strvajoin(3, pwd, "/", dir);
	return (new_dir);
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
			if (directory[0] == '/')
				get_add_pwd(directory, get_shell_env_value("PWD", shell));
		}
	}
	return (0);
}

int	ft_cd(const char **argv, t_shell *shell_state)
{
	return (internal_cd(argv[1], shell_state, TRUE));
}
