/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:13:46 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/19 12:12:20 by mgautier         ###   ########.fr       */
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

static void get_add_pwd(char **dir, const char *pwd)
{
	char	*new_dir;

	if (last_char_of(pwd) == '/')
		new_dir = ft_strjoin(pwd, *dir);
	else
		new_dir = ft_strvajoin(3, pwd, "/", *dir);
	ft_strdel(dir);
	*dir = new_dir;
}

/*
** OLDPWD shall be set before PWD is set to the new_value, since old_pwd is not
** a copy of PWD value, it points to it.
** Therefore modifying PWD value modify old_pwd content.
*/

static void	update_pwd(const char *new_pwd, t_shell *shell)
{
	const char	*old_pwd;
	char		*cwd;

	old_pwd = get_shell_env_value("PWD", shell);
	set_env_key("OLDPWD", old_pwd, shell);
	if (new_pwd != NULL)
		set_env_key("PWD", new_pwd, shell);
	else
	{
		cwd = getcwd(NULL, 0);
		set_env_key("PWD", cwd, shell);
		ft_strdel(&cwd);
	}
}

static const char	*handle_dot_dot_logically(char *directory)
{
	if (canonize_path(directory) == NULL || directory[0] == '\0')
		return (NULL);
	else
		return (directory);
}

size_t	relative_pathname(const char *directory)
{
	size_t		rel_part_begin;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	rel_part_begin = give_rel_path_from_abs(directory, cwd);
	ft_strdel(&cwd);
	return (rel_part_begin);
}

static int	more_internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically, char **directory)
{
	size_t	rel_part_index;
	int		return_is;

	rel_part_index = 0;
	if (dot_dot_logically)
	{
		get_add_pwd(directory, get_shell_env_value("PWD", shell));
		handle_dot_dot_logically(*directory);
		if (ft_strlen(*directory) >= PATH_MAX
				&& ft_strlen(dir_operand) < PATH_MAX)
			rel_part_index = relative_pathname(*directory);
	}
	if (chdir(*directory + rel_part_index) == -1)
	{
		ft_dprintf(STDERR_FILENO, "Error on cd when calling chdir"
				"\ndir is : %s\n", *directory);
		return_is = 1;
	}
	else
	{
		return_is = 0;
		if (dot_dot_logically)
			update_pwd(*directory, shell);
		else
			update_pwd(NULL, shell);
	}
	return (return_is);
}

static int	internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically)
{
	char	*directory;
	int			return_is;

	directory = produce_dir_operand(dir_operand,shell);
	if (directory == NULL)
		return_is = EXIT_FAILURE;
	else
	{
		return_is = more_internal_cd(dir_operand, shell,
				dot_dot_logically, &directory);
		ft_strdel(&directory);
	}
	return (return_is);
}

static int	apply_P(void *v_dot_dot_logic)
{
	t_bool	*dot_dot_logic;

	dot_dot_logic = v_dot_dot_logic;
	*dot_dot_logic = FALSE;
	return (0);
}

static int	apply_L(void *v_dot_dot_logic)
{
	t_bool	*dot_dot_logic;

	dot_dot_logic = v_dot_dot_logic;
	*dot_dot_logic = TRUE;
	return (0);
}

static t_bool	valid_options(int opt_ret)
{
	return (opt_ret == 0);
}

static void		cd_usage(const char *prog_name)
{
	ft_printf("%1$s: usage : %1$s [-L|-P] [dir]\n", prog_name);
}

int	ft_cd(const char **argv, t_shell *shell_state)
{
	t_bool		dot_dot_logically;
	t_synopsis	*syn;
	const t_apply_opt	opt[] = {apply_P, apply_L};
	const char			opt_letters[] = "PL";
	int					opt_numbers;

	syn = init_synopsis(opt_letters, opt, NULL, NULL);
	add_opt_validator(syn, valid_options);
	add_usage(syn, cd_usage, argv[0]);
	dot_dot_logically = TRUE;
	opt_numbers = apply_cmdline_opt(syn, argv, &dot_dot_logically);
	if (opt_numbers == USAGE_ERROR)
		return (1);
	return (internal_cd(argv[opt_numbers], shell_state, dot_dot_logically));
}
