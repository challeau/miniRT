#include "../inc/miniRT.h"

int	cross_exit(void)
{
	printf(">>> miniRT: cross exit...\n");
	exit(EXIT_SUCCESS);
	return (1);
}

int	esc_exit(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
	{
		printf(">>> miniRT: ESC exit...\n");
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int	exit_failure(void)
{
	printf("Error\nIssue encountered while setting up the mlx.\n");
	perror("perror says");
	exit(EXIT_FAILURE);
}

bool	setup(t_mlx *mlx, t_scene *s, int ac, char **av)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (false);
	get_scene_from_file(ac, av, s, mlx);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, s->win_res.x,
					s->win_res.y, "miniRT");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, s->win_res.x, s->win_res.y);
	if (mlx->win_ptr == NULL || mlx->img_ptr == NULL)
	{
		free(mlx->mlx_ptr);
		free(s->obj_list);
		free(s->lights_list);
		return(false);
	}
	printf(">>> miniRT: setup ok.\n");
	return (true);
}

int	main(int ac, char **av)
{
	t_scene		s;
	t_mlx	mlx;

	if (setup(&mlx, &s, ac, av) == false)
		exit_failure();
	printf(">>> miniRT: rendering...\n");
	generate_image(mlx, s);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr,
		mlx.img_ptr, 0, 0);
	free(s.obj_list);
	free(s.lights_list);
	mlx_key_hook(mlx.win_ptr, &esc_exit, &mlx);
	mlx_hook(mlx.win_ptr, 33, 1L << 2, cross_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
