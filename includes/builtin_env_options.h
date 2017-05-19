/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_options.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgautier <mgautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:04:57 by mgautier          #+#    #+#             */
/*   Updated: 2017/05/19 19:04:06 by mgautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_OPTIONS_H
# define BUILTIN_ENV_OPTIONS_H

int	apply_i(void *v_param);
int	apply_v(void *v_param);
int	apply_u(void *v_param, const char *arg);
int	apply_big_p(void *v_param, const char *arg);
int	apply_big_s(void *v_param, const char *arg);

#endif
