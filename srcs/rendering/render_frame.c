#include "../include/cub3D.h"

/**
 * @brief clear and draw map and player each frame
 */
int	render_frame(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	draw_map_2d(game);
	draw_player_2d(game);
	return (0);
}