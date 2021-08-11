#ifndef UTILS_H
# define UTILS_H

/* vectors and matrices */
typedef struct s_vec2f {
	float	x;
	float	y;
}		t_vec2f;

typedef struct s_vec3f {
	float	x;
	float	y;
	float	z;
}		t_vec3f;

typedef struct s_vec4f {
	float	x;
	float	y;
	float	z;
	float	w;
}		t_vec4f;

typedef struct s_vec2i {
	int	x;
	int	y;
}		t_vec2i;

typedef struct s_vec3i {
	int	x;
	int	y;
	int	z;
}		t_vec3i;

typedef struct s_vec3f	t_rgb;

enum		e_axis
{
	X,
	Y,
	Z,
	__TOTAL_ROT
};

/* vec2 */
float	vec2f_magnitude(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_normalize(t_vec2f vec);
t_vec2f	vec2f_lerp(t_vec2f a, t_vec2f b, float t);
float	vec2f_length(t_vec2f a);
float	vec2f_dot(t_vec2f a, t_vec2f b);

/* vec3 */
t_vec3f	vec3f_cross_product(t_vec3f a, t_vec3f b);
float	vec3f_magnitude(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_normalize(t_vec3f vec);
t_vec3f	vec3f_lerp(t_vec3f a, t_vec3f b, float t);
float	vec3f_length(t_vec3f a);
float	vec3f_dot(t_vec3f a, t_vec3f b);

/* vector-vector operations */
t_vec2f	vec2f_add_vec(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_sub_vec(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_mult_vec(t_vec2f a, t_vec2f b);
t_vec2f	vec2f_div_vec(t_vec2f a, t_vec2f b);

t_vec3f	vec3f_add_vec(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_sub_vec(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_mult_vec(t_vec3f a, t_vec3f b);
t_vec3f	vec3f_div_vec(t_vec3f a, t_vec3f b);

t_vec4f	vec4f_mult_vec(t_vec4f a, t_vec4f b);

/* vector-scalar operations */
t_vec2f	vec2f_add_scal(t_vec2f vec, float scal);
t_vec2f	vec2f_sub_scal(t_vec2f vec, float scal);
t_vec2f	vec2f_mult_scal(t_vec2f vec, float scal);
t_vec2f	vec2f_div_scal(t_vec2f vec, float scal);

t_vec3f	vec3f_add_scal(t_vec3f vec, float scal);
t_vec3f	vec3f_sub_scal(t_vec3f vec, float scal);
t_vec3f	vec3f_mult_scal(t_vec3f vec, float scal);
t_vec3f	vec3f_div_scal(t_vec3f vec, float scal);

/* mat3 */
void	get_vec3_identity_matrix(t_vec3f mat[3]);
void	get_roll_matrix(float theta, t_vec3f mat[3]);
void	get_pitch_matrix(float theta, t_vec3f mat[3]);
void	get_yaw_matrix(float theta, t_vec3f mat[3]);
void	get_and_apply_rotation_matrix(float theta, enum e_axis axis,
				t_vec3f *vec_addr);

/* mat4 */
void	get_vec4_identity_matrix(t_vec4f mat[4]);
void	get_and_apply_translation_matrix(t_vec3f *target_addr,
					 t_vec3f trans_vec);

/* vector-matrice operations */
t_vec3f	vec3f_mult_mat3(t_vec3f a, t_vec3f mat[3]);
t_vec3f	vec3f_mult_mat4(t_vec3f a, t_vec4f mat[4]);
t_vec4f	vec4f_mult_mat4(t_vec4f a, t_vec4f mat[4]);

/* maths */
float	fclampf(float value, float min, float max);

#endif
