#include "../include/cub3D.h"

static void	open_display(t_game *game);

void	handle_display(t_game *game)
{
	open_display(game);
}

static void	open_display(t_game *game)
{
	int	width;
	int	height;

	width = game->display.width;
	height = game->display.height;
	game->win_ptr = mlx_new_window(game->mlx_ptr, width, height, DISPLAY_NAME);
	if (!game->win_ptr)
		ft_exit_error(ERR_DISPLAY_OPEN);
	game->display.open = true;
}
