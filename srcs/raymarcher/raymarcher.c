#include "../../inc/miniRT.h"

/*
** calculates the distance between p, an arbitrary point in 3D space and
** all the objects in the scene.
** retruns the smallest distance and assigns to g_hit_object the index of the
** object that is the closest.
*/
float	get_dist(t_vec3f p, t_scene *s, t_object *list)
{
	uint8_t	i;
	float	(*sdfs[__OBJ_TOTAL])(t_vec3f pos, t_object obj);
	float	min_dist = MAX_DIST;
	float	buff_dist;

	i = 0;
	sdfs[0] = &sdf_sphere;
	sdfs[1] = &sdf_plane;
	sdfs[2] = &sdf_cylinder;
	sdfs[3] = &sdf_cone;
	while (list[i].type != e_OBJ_NONE && i < 20)
	{
		buff_dist = sdfs[list[i].type](p, list[i]);
		min_dist = fminf(buff_dist, min_dist);
		if (min_dist == buff_dist)
			s->obj_hit_ref = i;
		i++;
	}
	return (min_dist);
}

/*
** advances p, an arbitrary point in 3D space, along the camera direction ray
** with the distance to the closest object (dist_scene) until a surface is hit
** or the distance travelled is greater than 100 units.
*/
float	raymarch(t_cam cam, t_scene *s, t_object *list)
{
	size_t	i;
	t_vec3f p;
	float	dist_origin;
	float	dist_scene;

	i = 0;
	dist_origin = 0.0;
	while (i < MAX_STEPS)
	{
		p = vec3f_add_vec(cam.pos,
				vec3f_mult_scal(cam.orientation, dist_origin));
		dist_scene = get_dist(p, s, list);
		dist_origin += dist_scene;
		if (dist_origin > MAX_DIST || dist_scene < SURF_DIST)
			break ;
		i++;
	}
	return (dist_origin);
}

/*
** Gram-Schmidt process, creates the vectors that form the view/camera space.
** aka the look at.
*/
void	get_cam_look_at(t_cam *cam)
{
	t_vec3f up = {0, 1, 0};
	t_vec3f cam_back = vec3f_normalize(vec3f_sub_vec(cam->orientation,
							cam->pos));
	t_vec3f cam_right = vec3f_normalize(
		vec3f_cross_product(cam_back, up));
	t_vec3f cam_up = vec3f_cross_product(cam_right, cam_back);

	cam->axis[0] = (t_vec4f){cam_right.x, cam_right.y, cam_right.z, 0};
	cam->axis[1] = (t_vec4f){cam_up.x, cam_up.y, cam_up.z, 0};
	cam->axis[2] = (t_vec4f){-cam_back.x, -cam_back.y, -cam_back.z, 0};
	cam->axis[3] = (t_vec4f){0, 0, 0, 1};
}

t_vec3f get_cam_dir(t_vec2i pos, t_vec2f size, float fov)
{
	t_vec2f xy = vec2f_sub_vec((t_vec2f){pos.x, pos.y},
				   vec2f_div_scal(size, 2));
	float z = size.y / tan((fov * (M_PI / 180.0) / 2));
	return (vec3f_normalize((t_vec3f){xy.x, -xy.y, -z}));
}

/*
** returns the appropriate color of the pixel passed as argument.
** to see normals :
** t_vec3f n = get_surface_normal(surf_point, s.obj_list);
** n = vec3f_add_scal(vec3f_mult_scal(n, 0.5), 0.5);
** color = vec3f_mult_scal(vec3f_add_scal(vec3f_mult_scal(n, 0.5), 0.5), 255);
*/
t_rgb	get_pixel_color(t_vec2i pixel, t_scene s, t_cam cam)
{
	t_vec3f	uv;
	t_rgb		color;
	float		dist_scene;
	t_vec3f	surf_point;
//	t_vec3f	theta = cam.orientation;

//	uv = (t_vec3f){(pixel.x - 0.5 * s.win_res.x) / s.win_res.y,
//			-((pixel.y - 0.5 * s.win_res.y) / s.win_res.y), 1};
	uv = get_cam_dir(pixel, (t_vec2f){s.win_res.x, s.win_res.y} , cam.fov);
	get_cam_look_at(&cam);
	cam.orientation = vec3f_mult_mat4(uv, cam.axis);
	/* cam.orientation =  vec3f_normalize((t_vec3f){uv.x, uv.y, 1}); */
	/* get_and_apply_rotation_matrix(theta.x, X, &cam.orientation); */
	/* get_and_apply_rotation_matrix(theta.y, Y, &cam.orientation); */
	/* get_and_apply_rotation_matrix(theta.z, Z, &cam.orientation); */
	dist_scene = raymarch(cam, &s, s.obj_list);
	if (dist_scene <= MAX_DIST)
	{
		surf_point = vec3f_add_vec(cam.pos,
				vec3f_mult_scal(cam.orientation, dist_scene));
		color = get_light(surf_point, s,
					s.obj_list[s.obj_hit_ref].color);
		color = (t_vec3f){
			.x = pow(color.x, 0.4545),
			.y = pow(color.y, 0.4545),
			.z = pow(color.z, 0.4545),
		};
	}
	else
		color = (t_rgb){0,0,0};
//		color = vec3f_mult_scal(s.amb_light.color, s.amb_light.ratio);
	return (color);
}

void	generate_image(t_mlx mlx, t_scene s)
{
	t_vec2i		pixel;
	t_rgb		pixel_color;

	pixel = (t_vec2i){0, 0};
	while (pixel.y <= s.win_res.y)
	{
		while (pixel.x <= s.win_res.x)
		{
			pixel_color = get_pixel_color(pixel, s,
						s.cam);
			write_to_image(pixel_color, pixel, &mlx);
			pixel.x++;
		}
		pixel.x = 0;
		pixel.y++;
	}
	printf(">>> miniRT: main loop exited. congrats.\n");
}
