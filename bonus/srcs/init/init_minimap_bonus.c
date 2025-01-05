#include "../../include/cub3D_bonus.h"

void	init_minimap(t_game *game)
{
	game->minimap.width = 0;
	game->minimap.height = 0;
	game->minimap.pos_x = 0;
	game->minimap.pos_y = 0;
	game->minimap.tile_size = 0;
	game->minimap.player_x = 0;
	game->minimap.player_y = 0;
}
