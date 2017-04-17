/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:48:04 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/17 17:39:28 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stddef.h>

extern char	**environ;

void	print_strings(char **strings)
{
	size_t	index;

	index = 0;
	while (strings[index] != NULL)
	{
		ft_putendl(strings[index]);
		index++;
	}
}

char	**get_path(void)
{
	size_t	index;

	index = 0;
	while (environ[index] != NULL
			&& ft_strncmp("PATH=", environ[index], ft_strlen("PATH=")) != 0)
			index++;
	if (environ[index] == NULL)
		return (NULL);
	else
		return (ft_strsplit(environ[index] + ft_strlen("PATH="), ':'));
}

char	*get_raw_input(void)
{
	char *input;

	get_next_line(STDIN_FILENO, &input);
	return (input);
}

t_input	parse_input(char *raw)
{
	char **commands_and_args;

	commands_and_args = ft_strsplit(raw, ' ');
	ft_strdel(&raw);
	return (commands_and_args);
}

int main(void)
{
	char	*raw_input;
	t_input	input;
	int		return_status;
	char	**path;

	path = get_path();
	print_strings(path);
	while (1)
	{
		ft_printf(PROMPT);
		raw_input = get_raw_input();
		input = parse_input(raw_input);
		return_status = exec_input(input, path);
		ft_printf("Command return : %d\n", return_status);
	}
}
