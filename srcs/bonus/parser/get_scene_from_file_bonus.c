/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_from_file_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 20:21:45 by challeau          #+#    #+#             */
/*   Updated: 2021/06/05 20:21:45 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

/*
** allocates memory for the list of objects in the scene (limited to 20).
** allocates memory for the list of lights in the scene (limited to 10).
*/

void	alloc_scene_lists(t_scene *s)
{
	s->lights_list = (t_light *)malloc(10 * sizeof(t_light));
	s->obj_list = (t_object *)malloc(20 * sizeof(t_object));
	if (s->lights_list == NULL)
		parsing_error(*s, false, "allocation error.");
	if (s->obj_list == NULL)
	{
		free(s->lights_list);
		parsing_error(*s, false, "allocation error.");
	}
}

/*
** sets default values for the ambient light and window resolution to check
** later that they have been assigned.
** sets default values to the camera, and lights and objects lists.
*/

void	set_defaults(t_scene *s)
{
	uint8_t	i;

	i = 0;
	s->cam = (t_cam){.pos = {0.0, 1.0, 0.0},
		.orientation = {0.0, 0.0, 1.0},
		.fov = 70};
	s->win_res = (t_vec2i){1920, 1080};
	s->amb_light.ratio = 1;
	s->light_num = 0;
	alloc_scene_lists(s);
	while (i < 20)
	{
		s->obj_list[i] = (t_object){.type = e_OBJ_NONE};
		i++;
	}
}

/*
** assigns value to each element in the source file.
*/

void	handle_attributes(t_scene *s, char **attributes)
{
	int				enum_val;
	static uint8_t	obj_num = 0;
	bool			(*elem_set_fcts[__ELEM_TOTAL])(char **a,
						t_scene *s, uint8_t *o);

	enum_val = id_index(attributes[0]);
	elem_set_fcts[0] = &set_res;
	elem_set_fcts[1] = &set_amb_light;
	elem_set_fcts[2] = &set_cam;
	elem_set_fcts[3] = &set_light;
	elem_set_fcts[4] = &set_sphere;
	elem_set_fcts[5] = &set_plane;
	elem_set_fcts[6] = &set_cylinder;
	if (enum_val == -1)
		parsing_error(*s, true, "unknown object.");
	if (obj_num >= 20)
		parsing_error(*s, true, "too many objects.");
	if (elem_set_fcts[enum_val](attributes, s, &obj_num) == false)
		parsing_error(*s, true, "couldnt initialize an element.");
}

/*
** reads each non-empty line of the file.
** separates the attributes of the elements into a string array to be
** manipulated later.
*/

void	parse_source_file(int fd, t_scene *s)
{
	int		ret;
	char	*line;
	char	**obj_attributes;

	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		if (line[0] != '\0')
		{
			obj_attributes = ft_split(line, ' ');
			handle_attributes(s, obj_attributes);
			ft_memdel_strptr(obj_attributes);
		}
		ft_memdel(line);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
		parsing_error(*s, true, "cannot read your source file.");
}

/*
** checks arguments and opens the source file.
*/

void	get_scene_from_file(int ac, char **av, t_scene *s, void *mlx_ptr)
{
	int	fd;

	if (ac != 2)
		parsing_error(*s, false, "wrong number of arguments.");
	if (ft_compare_strs(av[1] + ft_strlen(av[1]) - 3, ".rt") != 1
		|| ft_strlen(av[1] + ft_strchr(av[1], '.')) != 3)
		parsing_error(*s, false, "argument must be a .rt file.");
	fd = open(av[1], O_RDONLY);
	set_defaults(s);
	parse_source_file(fd, s);
	fit_res_to_screen(s, mlx_ptr);
}
