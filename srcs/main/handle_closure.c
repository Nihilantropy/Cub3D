#include "../include/cub3D.h"

/**
 * @brief Handles the game closure process, cleaning up MLX window
 * and freeing allocated resources
 *
 * @param param Void pointer to game structure (cast to t_game internally)
 * @return int Returns 0 after successful cleanup and exit
 */
int	close_game(void *param)
{
	t_game	*game;

	game = param;
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free_all_and_exit(game, EXIT_SUCCESS);
	return (0);
}