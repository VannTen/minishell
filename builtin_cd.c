/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:13:46 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/17 11:42:59 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd_defs.h"
#include "shell_interface.h"
#include "path_constants.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#ifdef __gnu_linux__
# include <linux/limits.h>
#endif

/*
** Attempt to implement cd following the steps prescribed by POSIX at
** http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/

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

static char	*produce_dir_operand(const char *directory, const t_shell *shell)
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

static char	*get_add_pwd(const char *dir, const char *pwd)
{
	char	*new_dir;

	if (last_char_of(pwd) == '/')
		new_dir = ft_strjoin(pwd, dir);
	else
		new_dir = ft_strvajoin(3, pwd, "/", dir);
	return (new_dir);
}

/*
** OLDPWD shall be set before PWD is set to the new_value, since old_pwd is not
** a copy of PWD value, it points to it.
** Therefore modifying PWD value modify old_pwd content.
*/

static void	update_pwd(const char *new_pwd, t_shell *shell)
{
	const char	*old_pwd;

	old_pwd = get_shell_env_value("PWD", shell);
	set_env_key("OLDPWD", old_pwd, shell);
	set_env_key("PWD", new_pwd, shell);
}

static int	internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically)
{
	char	*directory;
	char	*tmp;
	char	*cwd;
	const char	*final_dir;
	int			return_is;

	directory = produce_dir_operand(dir_operand,shell);
	if (directory == NULL)
		return (EXIT_FAILURE);
	else
	{
		if (dot_dot_logically)
		{
			if (directory[0] != '/')
			{
				tmp = directory;
				directory =
					get_add_pwd(directory, get_shell_env_value("PWD", shell));
				ft_strdel(&tmp);
			}
			if (canonize_path(directory) == NULL || directory[0] == '\0')
				return (EXIT_FAILURE);
			if (ft_strlen(directory) >= PATH_MAX
					&& ft_strlen(dir_operand) < PATH_MAX)
			{
				cwd = getcwd(NULL, 0);
				final_dir = convert_path_abs_to_rel(directory, cwd);
				if (final_dir == NULL)
					final_dir = directory;
			}
			else
				final_dir = directory;
		}
		if (chdir(final_dir) == -1)
		{
			ft_dprintf(STDERR_FILENO, "Error on cd when calling chdir"
					"\ndir is : %s\nfinal dir is : %s", directory, final_dir);
			return_is = 1;
		}
		else
		{
			return_is = 0;
			update_pwd(final_dir, shell);
		}
		ft_strdel(&directory);
	}
	return (return_is);
}

int	ft_cd(const char **argv, t_shell *shell_state)
{
	return (internal_cd(argv[1], shell_state, TRUE));
}
