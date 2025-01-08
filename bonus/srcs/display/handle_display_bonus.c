#include "../../include/cub3D_bonus.h"

static bool	open_display(t_game *game);

/**
 * @brief Sets up game display by loading textures, initializing
 * window and minimap and getting initial mouse position
 *
 * @param game Game structure containing display data
 * @return bool true if setup successful, false otherwise
 */
bool	handle_display(t_game *game)
{
	if (!load_textures(game) || !open_display(game))
		return (false);
	game->display.open = true;
	if (!mlx_mouse_get_pos(game->mlx_ptr, game->win_ptr,
			&game->mouse.x, &game->mouse.y))
		return (ft_bool_putstr_fd(ERR_MOUSE_QUERY, 2));
	handle_mouse_appear(game, game->mouse.x, game->mouse.y);
	get_minimap_dimension(game);
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
