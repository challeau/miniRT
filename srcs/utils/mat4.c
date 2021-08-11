#include "../../inc/miniRT.h"

/*
** assigns the identity matrix to mat.
*/
void	get_vec4_identity_matrix(t_vec4f mat[4])
{
	mat[0] = (t_vec4f){1.0, 0.0, 0.0, 0.0};
	mat[1] = (t_vec4f){0.0, 1.0, 0.0, 0.0};
	mat[2] = (t_vec4f){0.0, 0.0, 1.0, 0.0};
	mat[3] = (t_vec4f){0.0, 0.0, 0.0, 1.0};
}

void	get_and_apply_translation_matrix(t_vec3f *target_addr,
					t_vec3f trans_vec)
{
	t_vec4f mat[4];
	t_vec3f res;

	mat[0] = (t_vec4f){1., 0., 0., 0};
	mat[1] = (t_vec4f){0., 1., 0., 0};
	mat[2] = (t_vec4f){0., 0., 1., 0};
	mat[3] = (t_vec4f){trans_vec.x, trans_vec.y, trans_vec.z, 1};
	res = vec3f_mult_mat4(*target_addr, mat);
	*target_addr = res;
}
