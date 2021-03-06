
#include "../../inc/miniRT.h"

/*
** sets default values for the ambient light, camera, light, window resolution,
** and objects lists.
*/

void	set_defaults(t_scene *s, t_mlx *mlx)
{
	uint8_t	i;

	i = 0;
	s->cam = (t_cam){.pos = {0.0, 1.0, 0.0},
		.orientation = {0.0, 0.0, 1.0},
		.fov = 70};

	s->lights_list = (t_light *)malloc(1 * sizeof(t_light));
	if (s->lights_list == NULL)
		parsing_error(s, false, mlx, "allocation error.");

	s->win_res = (t_vec2i){1920, 1080};
	s->amb_light.ratio = 1;
	s->obj_list = (t_object *)malloc(20 * sizeof(t_object));
	if (s->obj_list == NULL)
	{
		free(s->lights_list);
		parsing_error(s, false, mlx, "allocation error.");
	}
	while (i < 20)
	{
		s->obj_list[i] = (t_object){.type = e_OBJ_NONE};
		i++;
	}
}

/*
** assigns value to each element in the source file.
*/
char	*handle_attributes(t_scene *s, char **attributes)
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
	elem_set_fcts[7] = &set_cone;
	if (enum_val == -1)
		return("unknown object.");
	if (obj_num >= 20)
		return("too many objects.");
	if (elem_set_fcts[enum_val](attributes, s, &obj_num) == false)
		return("couldnt initialize an element.");
	return (NULL);
}

char	**get_elements(int fd, t_scene *s, t_mlx *mlx)
{
	int		i;
	int		ret;
	char	*line;
	char	**elements;

	i = 0;
	elements = (char**)malloc(50 * sizeof(char*));
	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		if (*line != 0)
		{
			elements[i] = ft_strdup(line);
			i++;
			elements[i] = NULL;
		}
		ft_memdel(line);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
	if (ret == -1)
	{
		free(elements);
		parsing_error(s, true, mlx, "couldn't open your file.");
	}
	return (elements);
}

void	parse_source_file(int fd, t_scene *s, t_mlx *mlx)
{
	int	i;
	char	**obj_attributes;
	char	**elements;
	char	*error;

	i = 0;
	elements = get_elements(fd, s, mlx);
	while(elements[i] != NULL)
	{
		obj_attributes = ft_split(elements[i], ' ');
		error = handle_attributes(s, obj_attributes);
		ft_memdel_strptr(obj_attributes);
		if (error != NULL)
		{
			ft_memdel_strptr(elements);
			parsing_error(s, true, mlx, error);
		}
		i++;
	}
	ft_memdel_strptr(elements);
}

/*
** checks arguments and opens the source file.
*/

void	get_scene_from_file(int ac, char **av, t_scene *s, t_mlx *mlx)
{
	int	fd;

	if (ac != 2)
		parsing_error(s, false, mlx, "wrong number of arguments.");
	if (ft_compare_strs(av[1] + ft_strlen(av[1]) - 3, ".rt") != 1
		|| ft_strlen(av[1] + ft_strchr(av[1], '.')) != 3)
		parsing_error(s, false, mlx, "argument must be a .rt file.");
	fd = open(av[1], O_RDONLY);
	set_defaults(s, mlx);
	parse_source_file(fd, s, mlx);
	fit_res_to_screen(s, mlx->mlx_ptr);
}
