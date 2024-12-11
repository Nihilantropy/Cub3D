#include "../include/so_long.h"

static void	open_display(t_game *game);
static void	get_win_size(t_game *game);

void	handle_display(t_game *game)
{
	get_win_size(game);
	open_display(game);
	// init_sprites(game);
	// draw_map(game);
	return ;
}

static void	open_display(t_game *game)
{
	window	width;
	window	height;

	width = game->win.width;
	height = game->win.height;
	game->mlx_win = mlx_new_window(game->mlx_ptr, width, height, DISPLAY_NAME);
}

static void	get_win_size(t_game *game)
{
	game->win.width = game->map.col * TILE_SIZE;
	game->win.height = game->map.row * TILE_SIZE;
}