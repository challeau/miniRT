/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 23:10:06 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 23:10:06 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/* returns the normal to the object at surface point p. */
t_vec3f	get_surface_normal(t_vec3f p, t_scene s, t_object *list)
{
	float	dist;
	float	eps;
	t_vec3f	n;

	dist = get_dist(p, &s, list);
	eps = 0.01;
	n = (t_vec3f){
		get_dist((t_vec3f){p.x + eps, p.y, p.z}, &s, list) - dist,
		get_dist((t_vec3f){p.x, p.y + eps, p.z}, &s, list) - dist,
		get_dist((t_vec3f){p.x, p.y, p.z + eps}, &s, list) - dist,
	};
	return (vec3f_div_scal(n, eps));
}

/* returns true if surf_point is in the shadow of an object. */
bool	get_shadow(t_vec3f surf_point, t_scene s, t_object *objs, t_light light)
{
	t_cam	sh_cam;
	float	dist;
	t_vec3f	light_dir;

	light_dir =  vec3f_normalize(vec3f_sub_vec(surf_point, light.pos));
	sh_cam.pos = vec3f_sub_vec(light.pos, light_dir);
	sh_cam.orientation = light_dir;
	dist = raymarch(sh_cam, &s, objs);
	if (dist < vec3f_magnitude(surf_point, light.pos))
		return (true);
	return (false);
}

t_rgb	ambient_light(t_amb_light amb_light, t_rgb obj_color)
{
	t_rgb	color;

	color = vec3f_mult_scal(amb_light.color, amb_light.ratio);
	color = vec3f_mult_vec(color, obj_color);
//	color = vec3f_div_scal(color, 255);
	return (color);
}

t_rgb	diffuse_light(t_vec3f surf_point, t_scene s, t_light light)
{
	t_vec3f	surf_normal;
	t_vec3f	light_dir;
	float	diffuse_factor;
	t_vec3f	diffuse_light;

	surf_normal = get_surface_normal(surf_point, s, s.obj_list);
	light_dir = vec3f_normalize(vec3f_sub_vec(light.pos, surf_point));
	diffuse_factor = vec3f_dot(surf_normal, light_dir);
	diffuse_light = vec3f_mult_scal(light.color, diffuse_factor);
	diffuse_light = vec3f_mult_scal(diffuse_light, light.ratio);
	return (diffuse_light);
}


t_rgb	get_light(t_vec3f surf_point, t_scene s, t_rgb obj_color)
{
	t_rgb	color;
	t_rgb	ambient;
	t_rgb	diffuse;

	ambient = vec3f_mult_scal(s.amb_light.color, s.amb_light.ratio);
	diffuse = diffuse_light(surf_point, s, *s.lights_list);
	color = vec3f_add_vec(ambient, diffuse);
	color = vec3f_mult_vec(color, obj_color);
	if (get_shadow(surf_point, s, s.obj_list, *s.lights_list) == true)
		color = vec3f_lerp((t_vec3f){0,0,0}, color, s.amb_light.ratio);
	return (color);
}

/* t_rgb	get_light(t_vec3f surf_point, t_scene s, t_rgb obj_color) */
/* { */
/* 	uint8_t i; */
/* 	t_rgb	color; */

/* 	i = 0; */
/* 	color = ambient_light(s.amb_light, obj_color); */
/* 	while (i < s.light_num) */
/* 	{ */
/* 		if (s.lights_list[i].ratio != 0) */
/* 			break ; */
/* 		color = vec3f_add_vec(color, diffuse_light(surf_point, s, */
/* 							    s.lights_list[i], */
/* 							    obj_color)); */
/*  		if (get_shadow(surf_point, s, s.obj_list, s.lights_list[i]) */
/* 		    == true) */
/*  			color = vec3f_lerp( */
/* 				(t_vec3f){0,0,0}, color, s.amb_light.ratio); */
/*  		i++; */
/* 	} */
/* 	return (color); */
/* } */
