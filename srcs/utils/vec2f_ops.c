#include "../../inc/miniRT.h"

t_vec2f	vec2f_add_vec(t_vec2f a, t_vec2f b)
{
	t_vec2f	new;

	new = (t_vec2f){a.x + b.x, a.y + b.y};
	return (new);
}

t_vec2f	vec2f_sub_vec(t_vec2f a, t_vec2f b)
{
	t_vec2f	new;

	new = (t_vec2f){a.x - b.x, a.y - b.y};
	return (new);
}

t_vec2f	vec2f_mult_vec(t_vec2f a, t_vec2f b)
{
	t_vec2f	new;

	new = (t_vec2f){a.x * b.x, a.y * b.y};
	return (new);
}

t_vec2f	vec2f_div_vec(t_vec2f a, t_vec2f b)
{
	t_vec2f	new;

	new = (t_vec2f){a.x / b.x, a.y / b.y};
	return (new);
}
