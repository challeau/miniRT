/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:37:24 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 12:37:24 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** returns a scalar representing how similar vectors a and b are.
*/

float	vec3f_dot(t_vec3f a, t_vec3f b)
{
	float	res;

	res = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (res);
}

/*
** returns a vector that is perpendicular to vectors a and b.
** aka a normal to the plane containing them.
*/

t_vec3f	vec3f_cross_product(t_vec3f a, t_vec3f b)
{
	t_vec3f	res;

	res.x = (a.y * b.z) - (b.y * a.z);
	res.y = (a.z * b.x) - (b.z * a.x);
	res.z = (a.x * b.y) - (b.x * a.y);
	return (res);
}

/*
** returns the distance between to vectors.
** that result is the length of vector a if b is the origin vector (0,0,0).
*/

float	vec3f_magnitude(t_vec3f a, t_vec3f b)
{
	float	x;
	float	y;
	float	z;

	x = (b.x - a.x) * (b.x - a.x);
	y = (b.y - a.y) * (b.y - a.y);
	z = (b.z - a.z) * (b.z - a.z);
	return (sqrt(x + y + z));
}

/*
** returns a unit vector that points in the same direction as the argument
** but is of size 1.
*/

t_vec3f	vec3f_normalize(t_vec3f vec)
{
	t_vec3f	norm_vec;
	float	vec_len;

	vec_len = vec3f_magnitude(vec, (t_vec3f){0, 0, 0});
	norm_vec.x = vec.x / vec_len;
	norm_vec.y = vec.y / vec_len;
	norm_vec.z = vec.z / vec_len;
	return (norm_vec);
}

/*
** linear interpolation between vectors a and b by t.
*/

t_vec3f	vec3f_lerp(t_vec3f a, t_vec3f b, float t)
{
	t_vec3f	res;

	res.x = a.x + (b.x - a.x) * t;
	res.y = a.y + (b.y - a.y) * t;
	res.z = a.z + (b.z - a.z) * t;
	return (res);
}
