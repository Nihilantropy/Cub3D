#include "../include/cub3D.h"

/**
 * @brief draw the player on the 2D map based on their exact position.
 * This function ensures smooth rendering and is called at every player movement.
 */
void	draw_player_2d(t_game *game)
{
	double x_world;
	double y_world;
	int x_screen;
	int y_screen;
	void *player_img;

	x_world = game->player.pos.x;
	y_world = game->player.pos.y;
	x_screen = (int)(x_world * MINI_CELL_SIZE - MINI_PLAYER_SIZE / 2);
	y_screen = (int)(y_world * MINI_CELL_SIZE - MINI_PLAYER_SIZE / 2);
	player_img = game->minimap.images.player;
	mlx_put_image_to_window(
		game->mlx_ptr,
		game->win_ptr,
		player_img,
		x_screen,
		y_screen
	);
}