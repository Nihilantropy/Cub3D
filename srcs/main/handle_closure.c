#include "../include/cub3D.h"

int	close_game(void *param)
{
	t_game	*game;

	game = param;
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_all(game);
	exit (0);
}