#include "../include/cub3D.h"

static void	draw_cell(t_game *game, int x, int y, char cell);

/**
 * @brief draw each cell for top-down 2d view
 * this function gets called only once at start.
 * player is rendered separatly.
 */
void	draw_map_2d(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map.matrix[y])
	{
		x = 0;
		while (game->map.matrix[y][x])
		{
			draw_cell(game, x, y, game->map.matrix[y][x]);
			x++;
		}
		y++;
	}
}

static void	draw_cell(t_game *game, int x, int y, char cell)
{
	void *img_to_draw;

	img_to_draw = NULL;
	if (cell == WALL)
		img_to_draw = game->minimap.images.wall;
	else if (cell == FLOOR || is_player_char(cell))
		img_to_draw = game->minimap.images.floor;
	else
		img_to_draw = game->minimap.images.unknown;
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img_to_draw, x * 64, y * 64);
}
