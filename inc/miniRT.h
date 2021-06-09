#ifndef MINIRT_H
# define MINIRT_H
# include <assert.h>
# include <fcntl.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/Xlib.h>
# include "libft/libft.h"

# define MAX_STEPS 100
# define MAX_DIST 100.0
# define SURF_DIST .01

# define ESC 0xff1b

/* OBJECT DEFINITIONS */
/* vectors and matrices */
typedef struct s_vec2f {
	float	x;
	float	y;
}		t_vec2f;

typedef struct s_vec3f {
	float	x;
	float	y;
	float	z;
}		t_vec3f;

typedef struct s_vec2i {
	int	x;
	int	y;
}		t_vec2i;

typedef struct s_vec3i {
	int	x;
	int	y;
	int	z;
}		t_vec3i;

typedef struct s_vec3f	t_rgb;

enum		e_axis
{
	X,
	Y,
	Z,
	__TOTAL_ROT
};

/* mlx related */
typedef struct s_mlx_obj{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
}		t_mlx_obj;

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
	t_vec3f	axis[4];
}		t_cam;

enum		e_elements {
	e_ELEM_RES,
	e_ELEM_AMBL,
	e_ELEM_CAM,
	e_ELEM_LIGHT,
	e_ELEM_SPHERE,
	e_ELEM_PLANE,
	e_ELEM_CYLINDER,
	__ELEM_TOTAL,
};

enum		e_objects {
	e_OBJ_SPHERE,
	e_OBJ_PLANE,
	e_OBJ_CYLINDER,
	e_OBJ_NONE,
	__OBJ_TOTAL,
};

typedef struct s_object {
	enum e_objects	type;
	t_vec3f			pos;
	t_rgb			color;
	t_vec3f			orientation;

	union	u_data {
		struct s_sphere {
			float	diameter;
		}	sphere;
		struct s_cylinder {
			float	length;
			float	diameter;
		}	cylinder;
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

typedef struct s_all {
	t_mlx_obj	mlx;
	t_scene		scene;
}		t_all;

/* PARSER */
void	get_scene_from_file(int ac, char **av, t_scene *s, void *mlx_ptr);
void	parse_source_file(int fd, t_scene *s);
void	set_defaults(t_scene *s);
void	alloc_scene_lists(t_scene *scene);
void	handle_attributes(t_scene *s, char **attributes);

/* scene elements set fcts */
bool	set_res(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_amb_light(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_cam(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_light(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_sphere(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_plane(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_square(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_cylinder(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_triangle(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_capsule(char **attributes, t_scene *scene, uint8_t *obj_num);

/* parser utils */
int		ft_compare_strs(const char *str1, const char *str2);
bool	get_elem_color(const char *attribute, t_vec3f *pos);
bool	get_elem_orientation(const char *attribute, t_vec3f *pos);
bool	get_elem_position(const char *attribute, t_vec3f *pos);
int		id_index(const char *id);
void	swap_strs(char **str1, char **str2);

/* check fcts and error handling */
void	parsing_error(t_scene s, bool is_scene_alloc, char *error);
void	fit_res_to_screen(t_scene *s, void *mlx_ptr);
void	check_necessary_elements(t_scene *s, void *mlx_ptr);
bool	check_attributes(char **attributes, uint8_t expected_num);
bool	check_vector_parsing(const char *attribute);

/* RAYMARCHER */
void	get_cam_look_at(t_cam *cam);

t_rgb	get_pixel_color(t_vec2i pixel, t_scene s, t_cam cam);
float	raymarch(t_cam cam, t_object *list);
float	get_dist(t_vec3f p, t_object *list);

/* signed distance functions */
float	sdf_sphere(t_vec3f pos, t_object obj);
float	sdf_plane(t_vec3f pos, t_object obj);
float	sdf_cylinder(t_vec3f pos, t_object obj);

/* get_light */
t_rgb	get_light(t_vec3f surf_point, t_scene s, t_rgb obj_color);
t_rgb	ambient_light(t_amb_light amb_light, t_rgb obj_color);
t_rgb	diffuse_light(t_vec3f surf_point, t_scene s, t_light light,
			t_rgb obj_color);
t_vec3f	get_surface_normal(t_vec3f p, t_object *list);

/* utils */
void	assign_sdfs_array(float (*(*sdfs)[__OBJ_TOTAL])(t_vec3f, t_object));
t_vec3f	normalize_screen_coordinates(t_vec2i pixel, t_vec2i res);

/* UTILS */
/* vectors
** vectors are points represented by their coordinates in 2d or 3d space. */
float	vec3f_dot(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_cross_product(t_vec3f a, t_vec3f b);
float	vec3f_magnitude(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_normalize(t_vec3f vec);
t_vec3f	vec3f_lerp(t_vec3f a, t_vec3f b, float t);
float	vec2f_length(t_vec2f a);
float	vec3f_length(t_vec3f a);

/* vector-vector operations. */
t_vec3f	vec3f_add_vec(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_sub_vec(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_mult_vec(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_div_vec(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_mod_vec(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_binand_vec(t_vec3f a, t_vec3f b);

/* vector-scalar operations */
t_vec3f	vec3f_add_scal(t_vec3f vec, float scal);
t_vec3f	vec3f_sub_scal(t_vec3f vec, float scal);
t_vec3f	vec3f_mult_scal(t_vec3f vec, float scal);
t_vec3f	vec3f_div_scal(t_vec3f vec, float scal);
t_vec3f	vec3f_mod_scal(t_vec3f vec, float scal);

/* matrices */
void	get_rotation_matrix(float theta, enum e_axis axis,
			t_vec3f mat[3]);
void	get_and_apply_rotation_matrix(float theta, enum e_axis axis,
			t_vec3f *vec_addr);
void	apply_rotation_matrix(t_vec3f *vec_addr, t_vec3f mat[3]);
void	get_vec3_identity_matrix(t_vec3f mat[3]);

/* matrices operations */
t_vec3f	vec3f_mult_mat3(t_vec3f a, t_vec3f mat[3]);
void	mat3_mult_mat3(t_vec3f m1[3], t_vec3f m2[3], t_vec3f *storage);
void	get_roll_matrix(float theta, t_vec3f mat[3]);
void	get_pitch_matrix(float theta, t_vec3f mat[3]);
void	get_yaw_matrix(float theta, t_vec3f mat[3]);

/* floats */
float	fclampf(float value, float min, float max);

/* IMAGE */
void	write_to_image(t_rgb color, t_vec2i pixel, t_mlx_obj *mlx);
void	handle_image(t_scene s, t_mlx_obj mlx);

/* EVENTS */
int		keys_handler(int keycode, void *param);

void	exit_failure(t_scene s, t_mlx_obj *mlx, char *error);
int		exit_success(void *param);

#endif
