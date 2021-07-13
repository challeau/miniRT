#include "../../inc/miniRT.h"

t_vec2f	vec2f_add_scal(t_vec2f vec, float scal)
{
	t_vec2f	new;

	new = (t_vec2f){vec.x + scal, vec.y + scal};
	return (new);
}

t_vec2f	vec2f_sub_scal(t_vec2f vec, float scal)
{
	t_vec2f	new;

	new = (t_vec2f){vec.x - scal, vec.y - scal};
	return (new);
}

t_vec2f	vec2f_mult_scal(t_vec2f vec, float scal)
{
	t_vec2f	new;

	new = (t_vec2f){vec.x * scal, vec.y * scal};
	return (new);
}

t_vec2f	vec2f_div_scal(t_vec2f vec, float scal)
{
	t_vec2f	new;

	new = (t_vec2f){vec.x / scal, vec.y / scal};
	return (new);
}
