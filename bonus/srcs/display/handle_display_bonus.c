#include "../../include/cub3D_bonus.h"

static bool	open_display(t_game *game);

/**
 * @brief Sets up game display by loading textures and initializing window
 *
 * @param game Game structure containing display data
 * @return bool true if setup successful, false otherwise
 */
bool	handle_display(t_game *game)
{
	if (!load_textures(game) || !open_display(game))
		return (false);
	game->display.open = true;
	return (true);
}

static bool	open_display(t_game *game)
{
	int	width;
	int	height;

	width = game->display.width;
	height = game->display.height;
	game->win_ptr = mlx_new_window(game->mlx_ptr, width, height, DISPLAY_NAME);
	if (!game->win_ptr)
		ft_bool_putstr_fd(ERR_DISPLAY_OPEN, 2);
	return (true);
}
