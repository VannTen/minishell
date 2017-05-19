/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 17:13:46 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/19 19:02:49 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_cd_defs.h"
#include "shell_interface.h"
#include "libft.h"

/*
** Attempt to implement cd following the steps prescribed by POSIX at
** http://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html
*/

/*
** OLDPWD shall be set before PWD is set to the new_value, since old_pwd is not
** a copy of PWD value, it points to it.
** Therefore modifying PWD value modify old_pwd content.
*/

static int		apply_big_p(void *v_dot_dot_logic)
{
	t_bool	*dot_dot_logic;

	dot_dot_logic = v_dot_dot_logic;
	*dot_dot_logic = FALSE;
	return (0);
}

static int		apply_big_l(void *v_dot_dot_logic)
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

int				ft_cd(const char **argv, t_shell *shell_state)
{
	t_bool				dot_dot_logically;
	t_synopsis			*syn;
	const t_apply_opt	opt[] = {apply_big_p, apply_big_l};
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
