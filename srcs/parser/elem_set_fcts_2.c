/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_set_fcts_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:03:17 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 14:03:17 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

bool	set_sphere(char **attributes, t_scene *scene, uint8_t *obj_num)
{
	t_object	new;

	if (!check_attributes(attributes, 4))
		return (false);
	if (!get_elem_position(attributes[1], &new.pos))
		return (false);
	new.data.sphere.diameter = ft_atof(attributes[2]);
	if (new.data.sphere.diameter < 0.)
		return (false);
	if (!get_elem_color(attributes[3], &new.color))
		return (false);
	new.type = e_OBJ_SPHERE;
	scene->obj_list[*obj_num] = new;
	*obj_num += 1;
	return (true);
}

bool	set_plane(char **attributes, t_scene *scene, uint8_t *obj_num)
{
	t_object	new;

	if (!check_attributes(attributes, 4))
		return (false);
	if (!get_elem_position(attributes[1], &new.pos))
		return (false);
	if (!get_elem_orientation(attributes[2], &new.orientation))
		return (false);
	if (!get_elem_color(attributes[3], &new.color))
		return (false);
	new.type = e_OBJ_PLANE;
	scene->obj_list[*obj_num] = new;
	*obj_num += 1;
	return (true);
}

bool	set_cylinder(char **attributes, t_scene *scene, uint8_t *obj_num)
{
	t_object	new;

	if (!check_attributes(attributes, 6))
		return (false);
	if (!get_elem_position(attributes[1], &new.pos))
		return (false);
	if (!get_elem_orientation(attributes[2], &new.orientation))
		return (false);
	new.data.cylinder.diameter = ft_atof(attributes[3]);
	new.data.cylinder.length = ft_atof(attributes[4]);
	if (new.data.cylinder.diameter < 0. || new.data.cylinder.length < 0.)
		return (false);
	if (!get_elem_color(attributes[5], &new.color))
		return (false);
	new.type = e_OBJ_CYLINDER;
	scene->obj_list[*obj_num] = new;
	*obj_num += 1;
	return (true);
}

bool	set_cone(char **attributes, t_scene *scene, uint8_t *obj_num)
{
	t_object	new;

	if (!check_attributes(attributes, 6))
		return (false);
	if (!get_elem_position(attributes[1], &new.pos))
		return (false);
	if (!get_elem_orientation(attributes[2], &new.orientation))
		return (false);
	new.data.cone.diameter = ft_atof(attributes[3]);
	new.data.cone.length = ft_atof(attributes[4]);
	if (new.data.cone.diameter < 0. || new.data.cone.length < 0.)
		return (false);
	if (!get_elem_color(attributes[5], &new.color))
		return (false);
	new.type = e_OBJ_CONE;
	scene->obj_list[*obj_num] = new;
	*obj_num += 1;
	return (true);
}
