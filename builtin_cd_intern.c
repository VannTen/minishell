/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_intern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 18:49:18 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/30 18:09:11 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd_defs.h"
#include "builtins_interface.h"
#include "shell_interface.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#ifdef __gnu_linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif

static const char	*handle_dot_dot_logically(char *directory)
{
	if (canonize_path(directory) == NULL || directory[0] == '\0')
		return (NULL);
	else
		return (directory);
}

void				cd_error(const char *dir, const char *shell)
{
	const char *error_message;

	if (access(dir, F_OK) == -1)
		error_message = "No such file or directory";
	else if (!is_dir(dir))
		error_message = "Not a directory";
	else if (access(dir, X_OK) == -1)
		error_message = "Permission denied";
	else
		error_message = "Unknown error";
	ft_dprintf(STDERR_FILENO, "%3$s: cd: %2$s: %1$s\n",
			error_message, dir, shell);
}

static int			change_to_dir(char **directory, size_t rel_part_index,
		t_shell *shell, t_bool dot_dot_logically)
{
	int			return_is;
	const char	*new_pwd;

	if (chdir(*directory + rel_part_index) == -1)
		return_is = BUILTIN_EXIT_FAILURE;
	else
	{
		if (dot_dot_logically)
			new_pwd = *directory;
		else
			new_pwd = NULL;
		return_is = update_pwd(new_pwd, shell) != NULL ?
			BUILTIN_EXIT_SUCCESS : BUILTIN_EXIT_FAILURE;
	}
	return (return_is);
}

static int			more_internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically, char **directory)
{
	size_t		rel_part_index;
	const char	*pwd;

	rel_part_index = 0;
	if (dot_dot_logically)
	{
		if (**directory != '/')
		{
			pwd = get_pwd(shell);
			if (pwd != NULL)
				get_add_path_before(directory, pwd);
			else
				return (BUILTIN_EXIT_FAILURE);
		}
		handle_dot_dot_logically(*directory);
		if (ft_strlen(*directory) >= PATH_MAX
				&& ft_strlen(dir_operand) < PATH_MAX)
			rel_part_index = relative_pathname(*directory);
	}
	return (change_to_dir(directory, rel_part_index, shell, dot_dot_logically));
}

int					internal_cd(const char *dir_operand, t_shell *shell,
		t_bool dot_dot_logically)
{
	char	*directory;
	int		return_is;
	t_bool	write_new_dir;

	write_new_dir = FALSE;
	directory = produce_dir_operand(dir_operand, shell, &write_new_dir);
	if (directory == NULL)
		return_is = BUILTIN_EXIT_FAILURE;
	else
	{
		return_is = more_internal_cd(dir_operand, shell,
				dot_dot_logically, &directory);
		if (return_is == BUILTIN_EXIT_FAILURE
				&& directory != NULL)
			cd_error(dir_operand == NULL || ft_strequ(dir_operand, "-") ?
					directory : get_file_part(directory),
					get_shell_name(shell));
		if (write_new_dir && return_is != BUILTIN_EXIT_FAILURE)
			ft_putendl(get_pwd(shell));
		ft_strdel(&directory);
	}
	return (return_is);
}
