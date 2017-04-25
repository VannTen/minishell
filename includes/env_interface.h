/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_interface.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 17:30:14 by mgautier          #+#    #+#             */
/*   Updated: 2017/04/24 20:09:26 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_INTERFACE_H
# define ENV_INTERFACE_H

const char	*get_env_value(const char *key);
char		*get_env_entry(const char *key);
char		*get_key(const char *env_entry);
char		**get_path(void);

char		**ft_putenv(const char *key, const char *value, char **env);
const char	*get_value(const char *env_entry);

#endif
