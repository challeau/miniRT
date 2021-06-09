/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:38:45 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 12:38:45 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** assigns the rotation matrice of theta about the axis to mat.
*/

void	get_rotation_matrix(float theta, enum e_axis axis,
				t_vec3f mat[3])
{
	static	void	(*const rot_fptr[__TOTAL_ROT])(float, t_vec3f *)
		= {&get_roll_matrix, &get_pitch_matrix, &get_yaw_matrix};

	rot_fptr[axis](theta, &mat[0]);
}

/*
** applies the rotation matrix to the vector passed as argument.
*/

void	apply_rotation_matrix(t_vec3f *vec_addr, t_vec3f mat[3])
{
	*vec_addr = vec3f_mult_mat3(*vec_addr, mat);
}

void	get_and_apply_rotation_matrix(float theta, enum e_axis axis,
		t_vec3f *vec_addr)
{
	t_vec3f	mat[3];

	get_rotation_matrix(theta, axis, &mat[0]);
	apply_rotation_matrix(vec_addr, &mat[0]);
}

/*
** assigns the identity matrix to mat.
*/

void	get_vec3_identity_matrix(t_vec3f mat[3])
{
	mat[0] = (t_vec3f){1, 0, 0};
	mat[1] = (t_vec3f){0, 1, 0};
	mat[2] = (t_vec3f){0, 0, 1};
}
