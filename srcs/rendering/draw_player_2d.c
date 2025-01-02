#include "../include/cub3D.h"

/**
 * @brief draw the player on the 2D map based on their exact position.
 * This function ensures smooth rendering and is called at every player movement.
 */
void	draw_player_2d(t_game *game)
{
	double x_world;
	double y_world;

	// Get player's world position
	x_world = game->player.pos.x;
	y_world = game->player.pos.y;

	// Convert player position to screen coordinates
	game->player.pos.x_screen = (int)(x_world * MINI_CELL_SIZE - MINI_PLAYER_SIZE / 2);
	game->player.pos.y_screen = (int)(y_world * MINI_CELL_SIZE - MINI_PLAYER_SIZE / 2);

	// Draw the player (yellow square)
	mlx_put_image_to_window(
		game->mlx_ptr,
		game->win_ptr,
		game->minimap.images.player,
		game->player.pos.x_screen - MINI_PLAYER_SIZE / 2,
		game->player.pos.y_screen - MINI_PLAYER_SIZE / 2
	);
}
