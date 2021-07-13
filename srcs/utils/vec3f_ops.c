#include "../../inc/miniRT.h"

t_vec3f	vec3f_add_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new = (t_vec3f){a.x + b.x, a.y + b.y, a.z + b.z};
	return (new);
}

t_vec3f	vec3f_sub_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new = (t_vec3f){a.x - b.x, a.y - b.y, a.z - b.z};
	return (new);
}

t_vec3f	vec3f_mult_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new = (t_vec3f){a.x * b.x, a.y * b.y, a.z * b.z};
	return (new);
}

t_vec3f	vec3f_div_vec(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new = (t_vec3f){a.x / b.x, a.y / b.y, a.z / b.z};
	return (new);
}

/*
** returns a scalar representing how similar vectors a and b are.
*/
float	vec3f_dot(t_vec3f a, t_vec3f b)
{
	float	res;

	res = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (res);
}
