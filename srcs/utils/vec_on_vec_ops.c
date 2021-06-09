/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_on_vec_ops.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:36:23 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 12:36:23 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vec3f	vec3f_add_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new = (t_vec3f){a.x + b.x, a.y + b.y, a.z + b.z};
	return (new);
}

t_vec3f	vec3f_sub_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new = (t_vec3f){a.x - b.x, a.y - b.y, a.z - b.z};
	return (new);
}

t_vec3f	vec3f_mult_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new = (t_vec3f){a.x * b.x, a.y * b.y, a.z * b.z};
	return (new);
}

t_vec3f	vec3f_div_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new = (t_vec3f){a.x / b.x, a.y / b.y, a.z / b.z};
	return (new);
}
