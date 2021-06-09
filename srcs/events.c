/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: challeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:46:06 by challeau          #+#    #+#             */
/*   Updated: 2021/02/08 13:46:06 by challeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
** frees all pointers allocated by the mlx and destroys image and window.
*/

void	free_mlx_ptrs(t_mlx_obj *mlx)
{
	if (mlx->img_ptr != NULL)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	if (mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
}

/*
** handles the events linked to keys press.
*/

int		keys_handler(int keycode, void *param)
{
	t_all	*all;

	all = param;
	if (keycode == ESC)
		exit_success(&all->mlx);
	if (keycode >= DIGIT_0 && keycode <= DIGIT_9)
		all->scene.cam_ref = keycode - DIGIT_0;
	return (0);
}

void	exit_failure(t_scene s, t_mlx_obj *mlx, char *error)
{
	free(s.obj_list);
	free(s.cam_list);
	free(s.lights_list);
	free_mlx_ptrs(mlx);
	printf("Error\nIssue encountered : %s\n", error);
	perror("perror says");
	exit(EXIT_FAILURE);
}

int		exit_success(void *param)
{
	t_all	*all;

	all = param;
	free(all->scene.obj_list);
	free(all->scene.cam_list);
	free(all->scene.lights_list);
	exit(EXIT_SUCCESS);
}
