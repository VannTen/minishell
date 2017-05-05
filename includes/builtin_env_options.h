/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_options.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:04:57 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/05 14:15:17 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_OPTIONS_H
# define BUILTIN_ENV_OPTIONS_H

int	apply_i(void *v_param);
int	apply_v(void *v_param);
int	apply_u(void *v_param, const char *arg);
int	apply_P(void *v_param, const char *arg);
int	apply_S(void *v_param, const char *arg);

#endif
