#include "../include/cub3D.h"

void	free_all_and_exit(t_game *game, int status)
{
	free_matrix((char **)game->map.matrix);
	free_minimap_images(game);
	free_bool_matrix(game->map.check.visited);
	free_info_list(&game->map.check.info);
	free_textures(game);
	free(game->mlx_ptr);
	exit(status);
}
