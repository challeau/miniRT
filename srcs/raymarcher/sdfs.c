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
	float	dist;

	dist = vec3f_magnitude(obj.pos, pos) - (obj.data.sphere.diameter / 2);
	return(dist);
}

float	sdf_plane(t_vec3f pos, t_object obj)
{
	float	dist;

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
	float	dist;

	pos = vec3f_sub_vec(pos, obj.pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.x), X, &pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.y), Y, &pos);
	get_and_apply_rotation_matrix(acos(obj.orientation.z), Z, &pos);
	dist = vec2f_length((t_vec2f){pos.x, pos.y}) -
		obj.data.cylinder.diameter;
	dist = fmaxf(dist, fabsf(pos.z) - (obj.data.cylinder.length / 2));
	return (dist);
}


float	sdf_cone(t_vec3f pos, t_object obj)
{
	float	dist;
	float	q;

	t_vec2f c = {sin(atan(obj.data.cone.diameter / obj.data.cone.length)),
		     cos(atan(obj.data.cone.diameter / obj.data.cone.length))};
	q = vec2f_length((t_vec2f){pos.x, pos.z});
	dist = vec2f_dot(c, (t_vec2f){q, pos.y});
	return (dist);
}



	
/* 	t_vec2f q = vec2f_mult_scal((t_vec2f){obj.pos.x / obj.pos.y, -1.0}, */
/* 				    obj.data.cone.length); */
/* 	t_vec2f w = (t_vec2f){vec2f_length((t_vec2f){pos.x, pos.z}), pos.y}; */
/* 	t_vec2f a = vec2f_sub_vec(w, vec2f_mult_scal(q,  */
/* 					  fclampf(vec2f_dot(w, q) / vec2f_dot(q, q), */
/* 							  0.0, 1.0))); */
/* 	t_vec2f b = vec2f_sub_vec(w, vec2f_mult_scal(q, fclampf(w.x/q.x, 0.0, 1.0))); */
/* 	float k = q.y < 0 ? -1 : 1; */
/* 	float d = fmin(vec2f_dot(a, a), vec2f_dot(b, b)); */
/* 	float s = fmax(k * (w.x * q.y - w.y * q.x), k * (w.y - q.y)); */
/* 	float dist = sqrt(d) * s < 0 ? -1 : 1; */
/* 	return (dist); */
/* } */

/* float	sdf_cone(t_vec3f pos, t_object obj) */
/* { */
/* 	float	dist; */
/* 	t_vec2f c; */
/* 	c.x = sin((obj.data.cone.diameter / 2) / obj.data.cone.length); */
/* 	c.y = cos((obj.data.cone.diameter / 2) / obj.data.cone.length); */
/* 	/\* get_and_apply_translation_matrix(&pos, vec3f_mult_scal(obj.pos, -1));*\/ */
/* 	/\* pos = vec3f_mult_mat3(pos, obj.rot_mat); *\/ */
/* 	/\* get_and_apply_rotation_matrix(acos(obj.orientation.x), X, &pos); *\/ */
/* 	/\* get_and_apply_rotation_matrix(acos(obj.orientation.y), Y, &pos); *\/ */
/* 	/\* get_and_apply_rotation_matrix(acos(obj.orientation.z), Z, &pos); *\/ */
/* 	dist = vec2f_length((t_vec2f){pos.x, pos.z}); */
/* 	dist = vec2f_dot(c, (t_vec2f){dist, pos.z}); */
/* 	return (dist); */
/* } */
