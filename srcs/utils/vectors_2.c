/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:12:55 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 12:12:55 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

float	vec2f_length(t_vec2f a)
{
	float	x;
	float	y;

	x = a.x * a.x;
	y = a.y * a.y;
	return (sqrt(x + y));
}

float	vec3f_length(t_vec3f a)
{
	float	x;
	float	y;
	float	z;

	x = a.x * a.x;
	y = a.y * a.y;
	z = a.z * a.z;
	return (sqrt(x + y + z));
}
