#include "../include/cub3D.h"

void	free_all(t_game *game)
{
	free_matrix((char **)game->map.matrix);
	free_minimap_images(game);
	free_bool_matrix(game->map.check.visited);
	free_info_list(&game->map.check.info);
	free_textures(game);
}
