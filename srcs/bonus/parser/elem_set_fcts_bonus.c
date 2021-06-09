/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_set_fcts_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:21:45 by challeau          #+#    #+#             */
/*   Updated: 2021/06/05 20:21:45 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

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
	t_light	new;

	if (check_attributes(attributes, 4))
		return (false);
	if (!get_elem_position(attributes[1], &new.pos))
		return (false);
	new.ratio = ft_atof(attributes[2]);
	if (new.ratio < 0. || new.ratio > 1.)
		return (false);
	if (!get_elem_color(attributes[3], &new.color))
		return (false);
	if (s->light_num < 10)
		s->lights_list[s->light_num] = new;
	s->light_num++;
	return (true);
}
