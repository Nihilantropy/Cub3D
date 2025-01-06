#include "../../include/cub3D_bonus.h"

/**
 * @brief Initializes the minimap parameters based on game display size
 * 
 * Calculates minimap dimensions and position to be displayed in the bottom right
 * corner of the screen. The size is scaled based on MINIMAP_SCALE constant.
 * Also determines the tile size based on map dimensions to fit within minimap.
 *
 * @param game Pointer to the main game structure
 */
void	get_minimap_dimension(t_game *game)
{
	t_minimap	*minimap;

	minimap = &game->minimap;
	minimap->width = (int)(game->display.width * MINIMAP_SCALE);
	minimap->height = (int)(game->display.height * MINIMAP_SCALE);
	minimap->tile_size = fmin(
		(minimap->width - 2 * MINIMAP_BORDER_SIZE) / game->map.width,
		(minimap->height - 2 * MINIMAP_BORDER_SIZE) / game->map.height
	);
	minimap->width = game->map.width * minimap->tile_size + 2 * MINIMAP_BORDER_SIZE;
	minimap->height = game->map.height * minimap->tile_size + 2 * MINIMAP_BORDER_SIZE;
	minimap->pos_x = game->display.width - minimap->width - MINIMAP_PADDING;
	minimap->pos_y = game->display.height - minimap->height - MINIMAP_PADDING;
	if (!init_static_minimap_texture(game))
		ft_exit_error("Failed to create minimap static texture\n");
}
