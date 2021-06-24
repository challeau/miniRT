#include "../inc/miniRT.h"

int	clean_exit(int keycode, t_mlx *mlx)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_scene		s;
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	get_scene_from_file(ac, av, &s, mlx.mlx_ptr);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, s.win_res.x,
					s.win_res.y, "miniRT");
	printf("setup ok\n");

	free(s.obj_list);
	free(s.lights_list);

	mlx_key_hook(mlx.win_ptr, &clean_exit, &mlx);
	mlx_hook(mlx.win_ptr, 33, 1L << 2, clean_exit, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
