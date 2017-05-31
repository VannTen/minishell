/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:09:07 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/31 16:41:08 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_defs.h"
#include "libft.h"
#include <unistd.h>

void	prompt_user(t_shell *shell)
{
	ft_printf("(last : %d)\n$>",
			get_exit_status(shell));
}
