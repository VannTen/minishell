/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_intern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:49:18 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/19 19:01:17 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd_defs.h"
#include "shell_interface.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#ifdef __gnu_linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

static void			get_add_pwd(char **dir, const char *pwd)
{
	char	*new_dir;

	if (last_char_of(pwd) == '/')
		new_dir = ft_strjoin(pwd, *dir);
	else
		new_dir = ft_strvajoin(3, pwd, "/", *dir);
	ft_strdel(dir);
	*dir = new_dir;
}

static void			update_pwd(const char *new_pwd, t_shell *shell)
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

static int			more_internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically, char **directory)
{
	size_t	rel_part_index;
	int		return_is;

	rel_part_index = 0;
	if (dot_dot_logically)
	{
		if (**directory != '/')
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

int					internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically)
{
	char	*directory;
	int		return_is;

	directory = produce_dir_operand(dir_operand, shell);
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
