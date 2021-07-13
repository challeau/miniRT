#include "../../inc/miniRT.h"

t_vec3f	vec3f_add_scal(t_vec3f vec, float scal)
{
	t_vec3f	new;

	new = (t_vec3f){vec.x + scal, vec.y + scal, vec.z + scal};
	return (new);
}

t_vec3f	vec3f_sub_scal(t_vec3f vec, float scal)
{
	t_vec3f	new;

	new = (t_vec3f){vec.x - scal, vec.y - scal, vec.z - scal};
	return (new);
}

t_vec3f	vec3f_mult_scal(t_vec3f vec, float scal)
{
	t_vec3f	new;

	new = (t_vec3f){vec.x * scal, vec.y * scal, vec.z * scal};
	return (new);
}

t_vec3f	vec3f_div_scal(t_vec3f vec, float scal)
{
	t_vec3f	new;

	new = (t_vec3f){vec.x / scal, vec.y / scal, vec.z / scal};
	return (new);
}
