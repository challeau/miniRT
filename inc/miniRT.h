#ifndef MINIRT_H
# define MINIRT_H
# include <assert.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/Xlib.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include "./utils.h"
# include "./scene.h"

# define MAX_STEPS 100
# define MAX_DIST 100.0
# define SURF_DIST .01

# define ESC 0xff1b

/* PARSER */
void	get_scene_from_file(int ac, char **av, t_scene *s, t_mlx *mlx);
void	parse_source_file(int fd, t_scene *s, t_mlx *mlx);
void	set_defaults(t_scene *s, t_mlx *mlx);
char	*handle_attributes(t_scene *s, char **attributes);

/* scene elements set fcts */
bool	set_res(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_amb_light(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_cam(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_light(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_sphere(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_plane(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_cylinder(char **attributes, t_scene *scene, uint8_t *obj_num);
bool	set_cone(char **attributes, t_scene *scene, uint8_t *obj_num);

/* parser utils */
int		ft_compare_strs(const char *str1, const char *str2);
bool	get_elem_color(const char *attribute, t_vec3f *pos);
bool	get_elem_orientation(const char *attribute, t_vec3f *pos);
bool	get_elem_position(const char *attribute, t_vec3f *pos);
int		id_index(const char *id);
void	swap_strs(char **str1, char **str2);

/* check fcts and error handling */
void	parsing_error(t_scene *s, bool is_scene_alloc, t_mlx *mlx, char *error);
void	fit_res_to_screen(t_scene *s, void *mlx_ptr);
void	check_necessary_elements(t_scene *s, void *mlx_ptr);
bool	check_attributes(char **attributes, uint8_t expected_num);
bool	check_vector_parsing(const char *attribute);

/* RAYMARCHER */
void	get_cam_look_at(t_cam *cam);
void	generate_image(t_mlx mlx, t_scene s);
t_rgb	get_pixel_color(t_vec2i pixel, t_scene s, t_cam cam);
float	raymarch(t_cam cam, t_scene *s, t_object *list);
float	get_dist(t_vec3f p, t_scene *s, t_object *list);

/* signed distance functions */
float	sdf_sphere(t_vec3f pos, t_object obj);
float	sdf_plane(t_vec3f pos, t_object obj);
float	sdf_cylinder(t_vec3f pos, t_object obj);
float	sdf_cone(t_vec3f pos, t_object obj);

/* get_light */
t_rgb	get_light(t_vec3f surf_point, t_scene s, t_rgb obj_color);
t_rgb	diffuse_light(t_vec3f surf_point, t_scene s, t_light light);
bool	get_shadow(t_vec3f surf_point, t_scene s, t_object *obj, t_light light);
t_vec3f	get_surface_normal(t_vec3f p, t_scene s, t_object *list);

/* utils */
void	assign_sdfs_array(float (*(*sdfs)[__OBJ_TOTAL])(t_vec3f, t_object));
t_vec3f	normalize_screen_coordinates(t_vec2i pixel, t_vec2i res);

/* IMAGE */
void	generate_image(t_mlx mlx, t_scene s);
void	write_to_image(t_rgb color, t_vec2i pixel, t_mlx *mlx);
/* void	handle_image(t_mlx mlx); */

#endif
