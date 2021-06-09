/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_and_error_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:29:12 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 13:29:12 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** if an issue was encountered, frees the objects and cameras lists and exits.
*/

void	parsing_error(t_scene s, bool is_scene_alloc, char *error)
{
	if (is_scene_alloc == true)
	{
		free(s.obj_list);
		free(s.lights_list);
	}
	printf("Error\nIssue encountered while parsing: %s\n", error);
	perror("perror says");
	exit(EXIT_FAILURE);
}

/*
** checks that the window resolution isn't bigger than that of the screen.
** if it is, adjusts it to fit in the screen.
*/

void	fit_res_to_screen(t_scene *s, void *mlx_ptr)
{
	t_vec2i	screen_res;

	mlx_get_screen_size(mlx_ptr, &screen_res.x, &screen_res.y);
	if (s->win_res.x > screen_res.x)
		s->win_res.x = screen_res.x;
	if (s->win_res.y > screen_res.y)
		s->win_res.y = screen_res.y;
	s->win_res.x = s->win_res.x;
	s->win_res.y = s->win_res.y;
}

/*
** checks that the vector passed as an attribute is correct.
*/

bool	check_vector_parsing(const char *attribute)
{
	uint8_t	i;
	char	**values;
	bool	res;

	if (ft_char_rep_count(',', attribute) != 2)
		return (false);
	i = 0;
	values = ft_split(attribute, ',');
	res = true;
	while (values[i] && i < 3)
	{
		if (ft_str_isnum(values[i]) == false)
			res = false;
		i++;
	}
	if (values[i] != NULL)
		res = false;
	ft_memdel_strptr(values);
	return (res);
}

/*
** checks that all the attributes to the element type are given
** in the source file.
** also checks that the attributes are numerical.
*/

bool	check_attributes(char **attributes, uint8_t expected_num)
{
	uint8_t	i;

	i = 1;
	while (attributes[i] && i < expected_num)
	{
		if (ft_str_isnum(attributes[i]) == false
			&& check_vector_parsing(attributes[i]) == false)
			return (false);
		i++;
	}
	if (i != expected_num || attributes[i] != NULL)
		return (false);
	return (true);
}
