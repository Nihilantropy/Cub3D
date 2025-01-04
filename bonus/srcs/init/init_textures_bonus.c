#include "../../include/cub3D_bonus.h"

void init_textures(t_game *game)
{
	game->textures.east = NULL;
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.floor_color = 0;
	game->textures.ceiling_color = 0;
	game->textures.floor = NULL;
	game->textures.ceiling = NULL;
	game->textures.size = 0;
}
