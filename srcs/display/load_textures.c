#include "../include/cub3D.h"

static bool load_single_texture(t_game *game, void **texture, char *path);

bool	load_textures(t_game *game)
{
	game->textures.size = TEXTURE_SIZE;

	if (!load_single_texture(game, &game->textures.north, PATH_TO_NORHT_WALL_TEXTURE) ||
		!load_single_texture(game, &game->textures.south, PATH_TO_SOUTH_WALL_TEXTURE) ||
		!load_single_texture(game, &game->textures.east, PATH_TO_EAST_WALL_TEXTURE) ||
		!load_single_texture(game, &game->textures.west, PATH_TO_WEST_WALL_TEXTURE) ||
		!load_single_texture(game, &game->textures.floor, PATH_TO_FLOOR_TEXTURE) ||
		!load_single_texture(game, &game->textures.ceiling, PATH_TO_CEILING_TEXTURE))
	{
		free_textures(game);
		return (false);
	}

	return (true);
}

static bool load_single_texture(t_game *game, void **texture, char *path)
{
	int	width;
	int	height;

	if (!game->mlx_ptr)
	{
		ft_putstr_fd("Error: MLX not initialized when loading texture\n", 2);
		return (false);
	}

	*texture = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
	if (!(*texture))
	{
		ft_putstr_fd("Error: Failed to load texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (false);
	}
	if (width != TEXTURE_SIZE || height != TEXTURE_SIZE)
	{
		ft_putstr_fd("Error: Texture size mismatch: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		mlx_destroy_image(game->mlx_ptr, *texture);
		*texture = NULL;
		return (false);
	}
	return (true);
}
