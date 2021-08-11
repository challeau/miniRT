#include "../../inc/miniRT.h"

/*
** assigns the identity matrix to mat.
*/
void	get_vec3_identity_matrix(t_vec3f mat[3])
{
	mat[0] = (t_vec3f){1, 0, 0};
	mat[1] = (t_vec3f){0, 1, 0};
	mat[2] = (t_vec3f){0, 0, 1};
}

/*
** a roll is a counterclockwise rotation of theta about the x axis.
** a 2D rotation is applied to the x and y coordinates, whereas the z
** coordinate remains constant.
*/
void	get_roll_matrix(float theta, t_vec3f mat[3])
{
	mat[0] = (t_vec3f){1, 0, 0};
	mat[1] = (t_vec3f){0, cos(theta), -sin(theta)};
	mat[2] = (t_vec3f){0, sin(theta), cos(theta)};
}

/*
** a pitch is a counterclockwise rotation of theta about the y axis.
*/
void	get_pitch_matrix(float theta, t_vec3f mat[3])
{
	mat[0] = (t_vec3f){cos(theta), 0, sin(theta)};
	mat[1] = (t_vec3f){0, 1, 0};
	mat[2] = (t_vec3f){-sin(theta), 0, cos(theta)};
}

/*
** a yaw is a counterclockwise rotation of theta about the z axis.
*/
void	get_yaw_matrix(float theta, t_vec3f mat[3])
{
	mat[0] = (t_vec3f){cos(theta), -sin(theta), 0};
	mat[1] = (t_vec3f){sin(theta), cos(theta), 0};
	mat[2] = (t_vec3f){0, 0, 1};
}


void	get_and_apply_rotation_matrix(float theta, enum e_axis axis,
		t_vec3f *vec_addr)
{
	t_vec3f	mat[3];
	static	void	(*const rot_fptr[__TOTAL_ROT])(float, t_vec3f *)
		= {&get_roll_matrix, &get_pitch_matrix, &get_yaw_matrix};

	rot_fptr[axis](theta, &mat[0]);
	*vec_addr = vec3f_mult_mat3(*vec_addr, mat);
}
