#include "../include/cub3D.h"

void	free_minimap_images(t_game *game)
{
	if (game->minimap.images.player)
		mlx_destroy_image(game->mlx_ptr, game->minimap.images.player);
	if (game->minimap.images.wall)
		mlx_destroy_image(game->mlx_ptr, game->minimap.images.wall);
	if (game->minimap.images.floor)
		mlx_destroy_image(game->mlx_ptr, game->minimap.images.floor);
	if (game->minimap.images.unknown)
		mlx_destroy_image(game->mlx_ptr, game->minimap.images.unknown);
}
