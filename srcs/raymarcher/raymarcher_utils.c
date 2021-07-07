/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarcher_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:50:11 by challeau          #+#    #+#             */
/*   Updated: 2021/02/07 13:50:11 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	assign_sdfs_array(float (*(*sdfs)[__OBJ_TOTAL])(t_vec3f, t_object))
{

	*sdfs[0] = NULL;
	*sdfs[1] = &sdf_sphere;
	*sdfs[2] = &sdf_plane;
	*sdfs[3] = NULL;
}

t_vec3f	normalize_screen_coordinates(t_vec2i pixel, t_vec2i res)
{
	t_vec3f	uv;

	uv = (t_vec3f){(pixel.x - 0.5 * res.x) / res.y,
		      -((pixel.y - 0.5 * res.y) / res.y), 1};
	return (uv);
}
