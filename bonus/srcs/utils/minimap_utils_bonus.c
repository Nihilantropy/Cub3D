#include "../../include/cub3D_bonus.h"

void	destroy_minimap_texture(t_game *game)
{
	if (game->minimap.static_texture)
		mlx_destroy_image(game->mlx_ptr, game->minimap.static_texture);	
}
