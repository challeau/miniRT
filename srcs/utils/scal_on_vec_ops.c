/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scal_on_vec_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:40:17 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 12:40:17 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
