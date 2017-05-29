/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 09:48:30 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/29 19:13:21 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_interface.h"
#include "shell_interface.h"
#include "error_interface.h"
#include "libft.h"
#include <unistd.h>

/*
** Attempt to follow the POSIX specifications defined at
** http://pubs.opengroup.org/onlinepubs/9699919799/
** utilities/V3_chap02.html#tag_18_09_01_01
*/

char		*find_exe_path(const char *exe_name, char **const path)
{
	size_t	index;
	char	*exe_full_path;

	index = 0;
	exe_full_path = NULL;
	if (path != NULL)
	{
		while (path[index] != NULL)
		{
			exe_full_path = ft_strvajoin(3, path[index], "/", exe_name);
			if (access(exe_full_path, F_OK) == 0)
				break ;
			else
				ft_strdel(&exe_full_path);
			index++;
		}
	}
	return (exe_full_path);
}

int			verify_command(const char *full_cmd_path, const char *shell_name)
{
	if (full_cmd_path == NULL)
	{
		shell_error(shell_name, COM_NOT_FOUND, full_cmd_path);
		return (COMMAND_NOT_FOUND);
	}
	if (access(full_cmd_path, X_OK) == -1)
	{
		shell_error(shell_name, PERM_DENIED, full_cmd_path);
		return (COULD_NOT_EXECUTE_COMMAND);
	}
	return (NO_ERROR);
}

static char	*final_command_path(char **args, t_shell *shell)
{
	char *exe_name;
	exe_name = find_exe_path(args[0], get_path(shell));
	if (exe_name != NULL)
	{
		ft_strdel(args);
		args[0] = exe_name;
	}
	return (exe_name);
}

int			search_external_command(char **args, t_shell *shell)
{
	char		*exe_name;
	int			command_search_result;

	if (!string_has_char(args[0], '/'))
		exe_name = final_command_path(args, shell);
	else
	{
		exe_name = args[0];
		if (access(exe_name, F_OK) == -1)
		{
			shell_error(get_shell_name(shell), NO_FILE, exe_name);
			return (COMMAND_NOT_FOUND);
		}
	}
	command_search_result = verify_command(exe_name, get_shell_name(shell));
	if (command_search_result != NO_ERROR)
		return (command_search_result);
	return (execute_command(args, get_env(shell)));
}

int			search_and_execute_command(char **args, t_shell *shell)
{
	t_builtin	builtin_utility;

	if (!(string_has_char(args[0], '/')))
	{
		builtin_utility = search_for_builtin(args[0]);
		if (builtin_utility != NULL)
			return (builtin_utility((const char**)args, shell));
	}
	return (search_external_command(args, shell));
}
