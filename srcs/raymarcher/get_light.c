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

t_rgb	diffuse_light(t_vec3f surf_point, t_scene s, t_light light)
{
	t_vec3f	surf_normal;
	t_vec3f	light_dir;
	float	diffuse_factor;
	t_vec3f	diffuse_light;
	t_cam	shade_cam;


	surf_normal = get_surface_normal(surf_point, s, s.obj_list);
	light_dir = vec3f_normalize(vec3f_sub_vec(light.pos, surf_point));
	diffuse_factor = vec3f_dot(surf_normal, light_dir);
	diffuse_light = vec3f_mult_scal((t_rgb){255, 255, 255}, diffuse_factor);
	diffuse_light = vec3f_mult_scal(diffuse_light, light.ratio);

	shade_cam.pos = light.pos;
	shade_cam.orientation = light_dir;
	if (raymarch(shade_cam, &s, s.obj_list) <= vec3f_magnitude(surf_point,
								light.pos))
		diffuse_light = (t_rgb){0,0,0};
	return (diffuse_light);
}

/* returns the reflection direction for a given incident vector vec and */
/* surface normal surf_norm. */
/* surf_norm should be normalized in order to achieve the desired result. */
t_vec3f	reflect(t_vec3f vec, t_vec3f surf_norm)
{
	t_vec3f	res;
	t_vec3f	inv_vec;

	inv_vec = (t_vec3f){-vec.x, -vec.y, -vec.z};
	res = vec3f_mult_scal(surf_norm, 2.0 * vec3f_dot(surf_norm, inv_vec));
	res = vec3f_sub_vec(inv_vec, res);
	return (res);
}

t_rgb	phong(t_vec3f surf_point, t_scene s, t_light light)
{
	t_vec3f	surf_normal;
	t_vec3f	light_dir;
	t_vec3f	reflect_dir;
	float		spec;
	t_rgb		specular;
	t_cam		shade_cam;

	surf_normal = get_surface_normal(surf_point, s, s.obj_list);
	light_dir = vec3f_normalize(vec3f_sub_vec(light.pos, surf_point));
	reflect_dir = reflect(light_dir, surf_normal);
	spec = pow(fmax(vec3f_dot(s.cam.orientation, reflect_dir), 0.0), 256); //shininess
	specular = vec3f_mult_scal(light.color, spec * 1.0);
	shade_cam.pos = light.pos;
	shade_cam.orientation = light_dir;
	if (raymarch(shade_cam, &s, s.obj_list) <= vec3f_magnitude(surf_point,
								light.pos))
		specular =  (t_rgb){0,0,0};
	return (specular);
}


t_rgb	get_light(t_vec3f surf_point, t_scene s, t_rgb obj_color)
{
	t_rgb	color;
	t_rgb	ambient;
	t_rgb	diffuse;
	t_rgb	specular;;

	ambient = vec3f_mult_scal(s.amb_light.color, s.amb_light.ratio);
	diffuse = diffuse_light(surf_point, s, *s.lights_list);
	specular = phong(surf_point, s, *s.lights_list);
//	color = vec3f_add_vec(ambient, diffuse);
	color = vec3f_add_vec(vec3f_add_vec(ambient, diffuse), specular);
	color = vec3f_mult_vec(color, obj_color);
	if (get_shadow(surf_point, s, s.obj_list, *s.lights_list) == true)
		color = vec3f_lerp((t_vec3f){0,0,0}, color, s.amb_light.ratio);
	return (color);
}
