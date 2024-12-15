#include "../include/cub3D.h"

void	init_minimap(t_game *game)
{
	game->minimap.images.player = NULL;
	game->minimap.images.wall = NULL;
	game->minimap.images.floor = NULL;
	game->minimap.images.unknown = NULL;
}
