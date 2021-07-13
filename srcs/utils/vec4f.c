#include "../../inc/miniRT.h"

t_vec4f	vec4f_mult_vec(t_vec4f a, t_vec4f b)
{
	t_vec4f	new;

	new.x = a.x * b.x;
	new.y = a.y * b.y;
	new.z = a.z * b.z;
	new.w = a.w * b.w;
	return (new);
}
