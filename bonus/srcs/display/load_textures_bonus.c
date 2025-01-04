#include "../../include/cub3D_bonus.h"

static bool load_single_texture(t_game *game, void **texture, char identifier);

/**
 * @brief Loads all game textures from XPM files
 *
 * @param game Game structure containing texture data
 * @return bool true if all textures loaded, false on any failure
 */
bool	load_textures(t_game *game)
{
	game->textures.size = TEXTURE_SIZE;

	if (!load_single_texture(game, &game->textures.north, 'N') ||
		!load_single_texture(game, &game->textures.south, 'S') ||
		!load_single_texture(game, &game->textures.east, 'E') ||
		!load_single_texture(game, &game->textures.west, 'W') ||
		!load_floor_and_ceiling(game))
	{
		return (ft_bool_putstr_fd(ERR_TEXTURE_LOAD, 2));
	}

	return (true);
}

/**
 * @brief Loads single texture from XPM file
 *
 * @param game Game structure containing MLX data
 * @param texture Pointer to store loaded texture
 * @param identifier Wall direction identifier (N,S,E,W)
 * @return bool true if texture loaded correctly, false on any error
 */
static bool load_single_texture(t_game *game, void **texture, char identifier)
{
	int		width;
	int		height;
	char	*path;

	path = find_texture_path(game->map.check.info, identifier);
	*texture = mlx_xpm_file_to_image(game->mlx_ptr, path, &width, &height);
	if (!(*texture))
	{
		free(path);
		return (false);
	}
	if (width != TEXTURE_SIZE || height != TEXTURE_SIZE)
	{
		mlx_destroy_image(game->mlx_ptr, *texture);
		*texture = NULL;
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

/**
 * @brief Retrieves texture path for specified identifier
 *
 * @param info List of map information nodes
 * @param identifier Texture identifier (N,S,E,W,F,C)
 * @return char* Duplicated path string, NULL if not found
 */
char	*find_texture_path(t_info *info, char identifier)
{
	t_info	*current_info;
	char	*content;

	current_info = info;
	content = NULL;
	while (current_info)
	{
		if (current_info->identifier == identifier)
		{
			content = ft_strdup(current_info->content);
			return (content);
		}
		current_info = current_info->next;
	}
	return (NULL);
}
