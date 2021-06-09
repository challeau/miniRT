/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:39:51 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 12:39:51 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vec3f	vec3f_mult_mat3(t_vec3f a, t_vec3f mat[3])
{
	t_vec3f	tmp;
	t_vec3f	res;

	tmp = vec3f_mult_vec(a, (t_vec3f){mat[0].x, mat[1].x, mat[2].x});
	res.x = tmp.x + tmp.y + tmp.z;
	tmp = vec3f_mult_vec(a, (t_vec3f){mat[0].y, mat[1].y, mat[2].y});
	res.y = tmp.x + tmp.y + tmp.z;
	tmp = vec3f_mult_vec(a, (t_vec3f){mat[0].z, mat[1].z, mat[2].z});
	res.z = tmp.x + tmp.y + tmp.z;
	return (res);
}

/*
** a roll is a counterclockwise rotation of theta about the x axis.
** a 2D rotation is applied to the x and y coordinates, whereas the z
** coordinate remains constant.
*/

void	get_roll_matrix(float theta, t_vec3f mat[3])
{
	mat[0] = (t_vec3f){1, 0, 0};
	mat[1] = (t_vec3f){0, cos(theta), -sin(theta)};
	mat[2] = (t_vec3f){0, sin(theta), cos(theta)};
}

/*
** a pitch is a counterclockwise rotation of theta about the y axis.
*/

void	get_pitch_matrix(float theta, t_vec3f mat[3])
{
	mat[0] = (t_vec3f){cos(theta), 0, sin(theta)};
	mat[1] = (t_vec3f){0, 1, 0};
	mat[2] = (t_vec3f){-sin(theta), 0, cos(theta)};
}

/*
** a yaw is a counterclockwise rotation of theta about the z axis.
*/

void	get_yaw_matrix(float theta, t_vec3f mat[3])
{
	mat[0] = (t_vec3f){cos(theta), -sin(theta), 0};
	mat[1] = (t_vec3f){sin(theta), cos(theta), 0};
	mat[2] = (t_vec3f){0, 0, 1};
}
