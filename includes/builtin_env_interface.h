/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_interface.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:41:04 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/19 19:45:54 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_INTERFACE_H
# define BUILTIN_ENV_INTERFACE_H

enum	e_env_options
{
	IGNORE_ENV,
	VERBOSE,
	OPT_NBR
};

enum	e_env_option_arg
{
	ALTPATH,
	STRING,
	REMOVE_NAME,
	OPT_ARG_NBR
};

# define ENV_SYNOPSIS "iv"
# define ENV_ARG_SYNOSPIS "PSu"
#endif
