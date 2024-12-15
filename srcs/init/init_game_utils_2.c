#include "../include/cub3D.h"

static void	init_minimap_images(t_game *game);

void	init_minimap(t_game *game)
{
	init_minimap_images(game);
	game->minimap.changed = false;
}

static void	init_minimap_images(t_game *game)
{
	game->minimap.images.player = NULL;
	game->minimap.images.wall = NULL;
	game->minimap.images.floor = NULL;
	game->minimap.images.unknown = NULL;
}
