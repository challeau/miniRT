#include "../../inc/miniRT.h"

/*
** returns a scalar representing how similar vectors a and b are.
*/
float	vec2f_dot(t_vec2f a, t_vec2f b)
{
	float	res;

	res = (a.x * b.x) + (a.y * b.y);
	return (res);
}

/*
** returns the distance between to vectors a and b.
** that result is the length of vector a if b is the origin vector (0,0,0).
*/
float	vec2f_magnitude(t_vec2f a, t_vec2f b)
{
	float	x;
	float	y;

	x = (b.x - a.x) * (b.x - a.x);
	y = (b.y - a.y) * (b.y - a.y);
	return (sqrt(x + y));
}

/*
** returns the length of the vector a.
*/
float	vec2f_length(t_vec2f a)
{
	float	x;
	float	y;

	x = a.x * a.x;
	y = a.y * a.y;
	return (sqrt(x + y));
}

/*
** returns a unit vector that points in the same direction as the argument
** but is of size 1.
*/
t_vec2f	vec2f_normalize(t_vec2f vec)
{
	t_vec2f	norm_vec;
	float	vec_len;

	vec_len = vec2f_magnitude(vec, (t_vec2f){0, 0});
	norm_vec.x = vec.x / vec_len;
	norm_vec.y = vec.y / vec_len;
	return (norm_vec);
}

/*
** linear interpolation between vectors a and b by t.
*/
t_vec2f	vec2f_lerp(t_vec2f a, t_vec2f b, float t)
{
	t_vec2f	res;

	res.x = a.x + (b.x - a.x) * t;
	res.y = a.y + (b.y - a.y) * t;
	return (res);
}
