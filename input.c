/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 18:35:17 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 19:06:13 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_defs.h"
#include "libft.h"
#include <unistd.h>
#include <stddef.h>

static void	strip_unwanted_char(char *iter)
{
	if (!ft_isprint(*iter))
		*iter = ' ';
}

char		*get_raw_input(void)
{
	char	*input;
	int		ret;

	ret = get_next_line(STDIN_FILENO, &input);
	if (ret != ONE_LINE_READ)
		return (NULL);
	else
	{
		ft_striter(input, strip_unwanted_char);
		return (input);
	}
}

t_input		parse_input(char *raw)
{
	char **commands_and_args;

	commands_and_args = ft_strsplit(raw, ' ');
	return (commands_and_args);
}

t_input		get_input(void)
{
	char	*raw_input;
	t_input	input;

	raw_input = get_raw_input();
	if (raw_input != NULL)
		input = parse_input(raw_input);
	else
		return (NULL);
	ft_strdel(&raw_input);
	return (input);
}

void		delete_input(t_input *to_del)
{
	ft_free_string_array(to_del);
	*to_del = NULL;
}
