/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:45:00 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 13:45:00 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*
** writes the RGB values of the pixel in the image string.
** if the endian is 0 (its value is system dependant), store the least
** significant byte first (blue).
** if the endian is 1, store the most significant byte first (alpha).
*/

void	write_to_image(t_rgb color, t_vec2i pixel, t_mlx *mlx)
{
	int		bpp;
	int		size_line;
	int		endian;
	size_t	pos;

	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &bpp,
			&size_line, &endian);
	pos = (pixel.y * size_line) + pixel.x * bpp / 8;
	if (endian == 0)
	{
		mlx->img_data[pos] = (int)color.z;
		mlx->img_data[pos + 1] = (int)color.y;
		mlx->img_data[pos + 2] = (int)color.x;
		mlx->img_data[pos + 3] = 1;
	}
	else if (endian == 1)
	{
		mlx->img_data[pos] = 1;
		mlx->img_data[pos + 1] = (int)color.x;
		mlx->img_data[pos + 2] = (int)color.y;
		mlx->img_data[pos + 2] = (int)color.z;
	}
}
