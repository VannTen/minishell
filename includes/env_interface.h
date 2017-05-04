/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_interface.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:30:14 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/04 15:23:29 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INTERFACE_H
# define ENV_INTERFACE_H
# include "libft.h"

/*
** Constants definitions
*/

# define PATH_SEP ':'

/*
** Get value from env
** Implementation file : env_tools_get.c
*/

const char	*get_env_value(const char *key, char **env);
char		*get_env_entry(const char *key, char **env);

/*
** Operations on env entry (key + value)
** Implementation file : env_entry.c
*/

char		*get_key(const char *env_entry);
const char	*get_value(const char *env_entry);
t_bool		key_are_equal(const char *searched_key, const char *env_entry);
char		*replace_env_entry(char *old_env_entry,
		const char *key, const char *new_value);

/*
** Operations on env
** Implementation file : env_tools_set.c
*/

char		**ft_putenv(const char *key, const char *value, char **env);
char		**ft_removeenv(const char *key, char **env);
char		**ft_setenv_intern(char **env, const char *setenv);
char		**empty_env(char **env);

/*
**
*/

char		**get_path(void);
t_bool		is_valid_setenv(const char *arg);


#endif
