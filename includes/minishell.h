/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 15:54:49 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/17 18:24:05 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Prompt shall be defined with printf style
*/

# define PROMPT "$>"

typedef char**	t_input;
typedef	int		(*t_builtin)(t_input);

/*
** Commands execution
** Implementation file : exec_command.c
*/

int		exec_input(t_input com_and_args, char **path);
#endif
