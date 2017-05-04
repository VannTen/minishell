/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_interface.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:30:14 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 09:52:05 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INTERFACE_H
# define ENV_INTERFACE_H
# include "libft.h"

/*
** Constants definitions
*/

# define PATH_SEP ':'

const char	*get_env_value(const char *key);
char		*get_env_entry(const char *key);
char		*get_key(const char *env_entry);
char		**get_path(void);
t_bool		is_valid_setenv(const char *arg);

char		**ft_putenv(const char *key, const char *value, char **env);
char		**ft_removeenv(const char *key, char **env);
const char	*get_value(const char *env_entry);
char		**ft_setenv_intern(char **env, const char *setenv);

#endif
