/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_set_fcts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:37:31 by challeau          #+#    #+#             */
/*   Updated: 2021/05/13 20:37:31 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

bool	set_res(char **attributes, t_scene *s,
		__attribute__((unused))uint8_t *obj_num)
{
	t_vec2i		win_res;
	static bool	is_set = false;

	if (is_set == true || !check_attributes(attributes, 3))
		return (false);
	win_res.x = ft_atoi(attributes[1]);
	win_res.y = ft_atoi(attributes[2]);
	if (win_res.x <= 0 || win_res.y <= 0)
		return (false);
	s->win_res.x = win_res.x;
	s->win_res.y = win_res.y;
	is_set = true;
	return (true);
}

bool	set_amb_light(char **attributes, t_scene *s,
		__attribute__((unused))uint8_t *obj_num)
{
	float		ratio;
	static bool	is_set = false;

	if (is_set == true || !check_attributes(attributes, 3))
		return (false);
	ratio = ft_atof(attributes[1]);
	if (ratio <= 0.0 || ratio > 1.0)
		return (false);
	s->amb_light.ratio = ratio;
	if (!get_elem_color(attributes[2], &s->amb_light.color))
		return (false);
	is_set = true;
	return (true);
}

bool	set_cam(char **attributes, t_scene *s,
		__attribute__((unused))uint8_t *obj_num)
{
	static bool	is_set = false;

	if (is_set == true || !check_attributes(attributes, 4))
		return (false);
	if (!get_elem_position(attributes[1], &s->cam.pos))
		return (false);
	if (!get_elem_orientation(attributes[2], &s->cam.orientation))
		return (false);
	s->cam.fov = ft_atoi(attributes[3]);
	if (s->cam.fov < 0 || s->cam.fov > 180)
		return (false);
	return (true);
}

bool	set_light(char **attributes, t_scene *s,
		__attribute__((unused))uint8_t *obj_num)
{
	t_light		new;
	static bool	is_set = false;

	if (is_set == true)
		return (false);
	if (!check_attributes(attributes, 3)
		&& !check_attributes(attributes, 4))
		return (false);
	if (!get_elem_position(attributes[1], &new.pos))
		return (false);
	new.ratio = ft_atof(attributes[2]);
	if (new.ratio < 0. || new.ratio > 1.)
		return (false);
	s->lights_list[0] = new;
	s->lights_list[0].color = (t_rgb){255, 255, 255};
	s->light_num++;
	return (true);
}
