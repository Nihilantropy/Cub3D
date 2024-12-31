#include "../include/cub3D.h"

void	free_textures(t_game *game)
{
	if (game->textures.north)
		mlx_destroy_image(game->mlx_ptr, game->textures.north);
	if (game->textures.south)
		mlx_destroy_image(game->mlx_ptr, game->textures.south);
	if (game->textures.east)
		mlx_destroy_image(game->mlx_ptr, game->textures.east);
	if (game->textures.west)
		mlx_destroy_image(game->mlx_ptr, game->textures.west);
	if (game->textures.floor)
		mlx_destroy_image(game->mlx_ptr, game->textures.floor);
	if (game->textures.ceiling)
		mlx_destroy_image(game->mlx_ptr, game->textures.ceiling);
}
