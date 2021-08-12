#ifndef SCENE_H
# define SCENE_H
#include <stdint.h>
# include "./utils.h"
# include "./minilibx-linux/mlx.h"

/* scene elements */
typedef struct s_amb_light {
	float	ratio;
	t_rgb	color;
}		t_amb_light;

typedef struct s_light {
	t_vec3f	pos;
	t_rgb	color;
	float	ratio;
}		t_light;

typedef struct s_ray {
	t_vec3f	origin;
	t_vec3f	direction;
}		t_ray;

typedef struct s_cam {
	t_vec3f	pos;
	t_vec3f	orientation;
	uint8_t	fov;
	t_vec4f	axis[4];
}		t_cam;

enum		e_elements {
	e_ELEM_RES,
	e_ELEM_AMBL,
	e_ELEM_CAM,
	e_ELEM_LIGHT,
	e_ELEM_SPHERE,
	e_ELEM_PLANE,
	e_ELEM_CYLINDER,
	e_ELEM_CONE,
	__ELEM_TOTAL,
};

enum		e_objects {
	e_OBJ_SPHERE,
	e_OBJ_PLANE,
	e_OBJ_CYLINDER,
	e_OBJ_CONE,
	e_OBJ_NONE,
	__OBJ_TOTAL,
};

typedef struct s_object {
	enum e_objects	type;
	t_vec3f			pos;
	t_rgb			color;
	t_vec3f			orientation;
	t_vec3f			rot_mat[3];

	union	u_data {
		struct s_sphere {
			float	diameter;
		}	sphere;
		struct s_cylinder {
			float	length;
			float	diameter;
		}	cylinder;
		struct s_cone {
			float		length;
			float		diameter;
		}	cone;
	}	data;
}		t_object;

typedef struct s_scene {
	t_vec2i		win_res;
	t_amb_light	amb_light;
	t_object	*obj_list;
	uint8_t		obj_hit_ref;
	t_light		*lights_list;
	uint8_t		light_num;
	t_cam		cam;
}		t_scene;

/* mlx related */
typedef struct s_mlx{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
}		t_mlx;

typedef struct s_all {
	t_mlx			mlx;
	t_scene		s;
}		t_all;

#endif
