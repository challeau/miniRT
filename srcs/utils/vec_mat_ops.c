#include "../../inc/miniRT.h"

t_vec3f	vec3f_mult_mat3(t_vec3f a, t_vec3f mat[3])
{
	t_vec3f	tmp;
	t_vec3f	res;

	tmp = vec3f_mult_vec(a, (t_vec3f){mat[0].x, mat[1].x, mat[2].x});
	res.x = tmp.x + tmp.y + tmp.z;
	tmp = vec3f_mult_vec(a, (t_vec3f){mat[0].y, mat[1].y, mat[2].y});
	res.y = tmp.x + tmp.y + tmp.z;
	tmp = vec3f_mult_vec(a, (t_vec3f){mat[0].z, mat[1].z, mat[2].z});
	res.z = tmp.x + tmp.y + tmp.z;
	return (res);
}

t_vec3f	vec3f_mult_mat4(t_vec3f a, t_vec4f mat[4])
{
	t_vec4f	tmp;

	tmp = (t_vec4f){a.x, a.y, a.z, 1};
	tmp = vec4f_mult_mat4(tmp, mat);
	return ((t_vec3f){tmp.x, tmp.y, tmp.z});
}

t_vec4f	vec4f_mult_mat4(t_vec4f a, t_vec4f mat[4])
{
	t_vec4f	tmp;
	t_vec4f	res;

	tmp = vec4f_mult_vec(a, (t_vec4f){mat[0].x, mat[1].x, mat[2].x,
					mat[3].x});
	res.x = tmp.x + tmp.y + tmp.z + tmp.w;
	tmp = vec4f_mult_vec(a, (t_vec4f){mat[0].y, mat[1].y, mat[2].y,
					mat[3].y});
	res.y = tmp.x + tmp.y + tmp.z + tmp.w;
	tmp = vec4f_mult_vec(a, (t_vec4f){mat[0].z, mat[1].z, mat[2].z,
					mat[3].z});
	res.z = tmp.x + tmp.y + tmp.z + tmp.w;
	tmp = vec4f_mult_vec(a, (t_vec4f){mat[0].w, mat[1].w, mat[2].w,
					mat[3].w});
	res.w = tmp.x + tmp.y + tmp.z + tmp.w;
	return (res);
}
