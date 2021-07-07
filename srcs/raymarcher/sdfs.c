/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdfs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 15:01:41 by challeau          #+#    #+#             */
/*   Updated: 2021/02/07 15:01:41 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** signed distance functions are used to calculate the distance between p, 
** a point in 3D space, and the surface of an object.
*/

float	sdf_sphere(t_vec3f pos, t_object obj)
{
	float dist;

	dist = vec3f_magnitude(obj.pos, pos) - (obj.data.sphere.diameter / 2);
	return(dist);
}

float	sdf_plane(t_vec3f pos, t_object obj)
{
	float dist;

	pos = vec3f_sub_vec(pos, obj.pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.x), X, &pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.y), Y, &pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.z), Z, &pos);

	dist = vec3f_dot(pos, vec3f_normalize(obj.orientation));
	dist += obj.pos.y;
	return (dist);
}

float	sdf_cylinder(t_vec3f pos, t_object obj)
{
	float dist;
//	get_and_apply_translation_matrix(&p, vec3f_mul_k(obj.pos, -1));
	pos = vec3f_sub_vec(pos, obj.pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.x), X, &pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.y), Y, &pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.z), Z, &pos);

	dist = vec2f_length((t_vec2f){pos.x, pos.y}) - obj.data.cylinder.diameter;
	dist = fmaxf(dist, fabsf(pos.z) - (obj.data.cylinder.length / 2));
	return (dist);
}

/* float	sdf_square(t_vec3f pos, t_object obj) */
/* { */
/* 	float size = obj.data.square.length; */
/* 	float dist; */

/* 	if (pos.x < 0){ */
/* 	} */

/* t_vec3f d; */

/* d = vec_sub((t_vec3f){fabsf(pos.x), fabsf(pos.y), fabsf(pos.z)}, obj.pos); */
/* d = vec_scal_sub(d, size); */
/* float res = vec_length( */
/* (t_vec3f){.x = fmaxf(fmax(d.x, d.y), 0.0) + fminf(fmaxf(d.x, d.y), 0.0), */
/* 			.y = 0.0, .z = d.z}); */
/* 	return (dist); */
/* } */


/* float	sdf_cylinder(t_vec3f pos, t_object obj) */
/* { */
/* 	return (1); */
/* } */

/* float	sdf_triangle(t_vec3f pos, t_object obj) */
/* { */
/* } */
