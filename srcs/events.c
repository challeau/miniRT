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

#include "../inc/miniRT.h"

/* /\* */
/* ** frees all pointers allocated by the mlx and destroys image and window. */
/* *\/ */

/* void	free_mlx_ptrs(t_mlx_obj *mlx) */
/* { */
/* //	if (mlx->img_ptr != NULL) */
/* //		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr); */
/* //	printf("img free\n"); */
/* 	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr); */
/* 	mlx_destroy_display(mlx->mlx_ptr); */
/* 	free(mlx->mlx_ptr); */
/* } */

/* /\* */
/* ** handles the events linked to keys press. */
/* *\/ */

/* int	keys_handler(int keycode, void *param) */
/* { */
/* 	t_all	*all; */

/* 	all = param; */
/* 	if (keycode == ESC) */
/* 		exit_success(&all); */
/* 	return (0); */
/* } */

/* void	exit_failure(t_mlx_obj *mlx, char *error) */
/* { */
/* 	if (mlx->win_ptr != NULL) */
/* 		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr); */
/* 	if (mlx->mlx_ptr != NULL) */
/* 	{ */
/* 		mlx_destroy_display(mlx->mlx_ptr); */
/* 		free(mlx->mlx_ptr); */
/* 	} */
/* 	printf("Error\nIssue encountered : %s\n", error); */
/* 	perror("perror says"); */
/* 	exit(EXIT_FAILURE); */
/* } */

/* int	exit_success(void *param) */
/* { */
/* 	t_all	*all; */

/* 	all = param; */
/* 	mlx_destroy_window(all->mlx.mlx_ptr, all->mlx.win_ptr); */
/* 	mlx_destroy_display(all->mlx.mlx_ptr); */
/* 	free(all->mlx.mlx_ptr); */
/* 	exit(EXIT_SUCCESS); */
/* 	return 0; */
/* } */
