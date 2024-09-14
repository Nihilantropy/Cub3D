#include "../include/cub3D.h"

void	free_all(t_game *game)
{
	free_matrix((char **)game->map.matrix);
	free_info_list(&game->map.check.info);
}
