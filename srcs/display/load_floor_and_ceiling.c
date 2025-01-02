#include "../include/cub3D.h"

static bool process_rgb_values(int *color, char **values);
static bool create_solid_color_texture(t_game *game, void **texture, int color);
static bool	load_color_texture(t_game *game, char identifier, 
							int *color_ptr, void **texture);

/**
 * @brief Creates floor and ceiling textures from RGB color values
 * 
 * @param game Game structure containing texture data
 * @return bool true if both textures created successfully, false otherwise
 */
bool load_floor_and_ceiling(t_game *game)
{
	if (!load_color_texture(game, 'F', &game->textures.floor_color,
						&game->textures.floor))
		return (ft_bool_putstr_fd(ERR_LOAD_FLOOR_RGB, 2));
	if (!load_color_texture(game, 'C', &game->textures.ceiling_color,
						&game->textures.ceiling))
		return (ft_bool_putstr_fd(ERR_LOAD_CEILING_RGB, 2));
	return (true);
}

/**
 * @brief Creates texture from RGB color for floor/ceiling
 *
 * @param game Game structure
 * @param identifier 'F' for floor, 'C' for ceiling
 * @param color_ptr Pointer to store RGB color value
 * @param texture Pointer to store created texture
 * @return bool true if texture created successfully, false otherwise
 */
static bool load_color_texture(t_game *game, char identifier, 
							int *color_ptr, void **texture)
{
	char	*rgb_str;
	char	**rgb_values;
	bool	success;

	rgb_str = find_texture_path(game->map.check.info, identifier);
	if (!rgb_str)
		return (false);
	rgb_values = ft_split(rgb_str, ',');
	free(rgb_str);
	if (!rgb_values)
		return (false);
	success = process_rgb_values(color_ptr, rgb_values);
	if (!success)
		return (false);
	return (create_solid_color_texture(game, texture, *color_ptr));
}

/**
 * @brief Creates solid color texture of specified dimensions
 *
 * @param game Game structure containing MLX data
 * @param texture Pointer to store created texture
 * @param color RGB color value to fill texture
 * @return bool true if texture created, false on failure
 */
static bool	create_solid_color_texture(t_game *game, void **texture, int color)
{
	int				x;
	int				y;
	t_render_state	state;

	*texture = mlx_new_image(game->mlx_ptr, TEXTURE_SIZE, TEXTURE_SIZE);
	if (!(*texture))
		return (false);
	state.img_data = (int *)mlx_get_data_addr(*texture, &state.bits_per_pixel,
								&state.line_length, &state.endian);
	y = 0;
	while (y < TEXTURE_SIZE)
	{
		x = 0;
		while (x < TEXTURE_SIZE)
		{
			state.img_data[y * (state.line_length / 4) + x] = color;
			x++;
		}
		y++;
	}
	return (true);
}

/**
 * @brief Validates and converts RGB string values to color integer
 *
 * @param color Pointer to store final RGB value
 * @param values Array of RGB strings to process
 * @return bool true if valid and converted, false otherwise
 */
static bool process_rgb_values(int *color, char **values)
{
	if (!check_rgb_values((const char **)values))
	{
		free_matrix(values);
		return (false);
	}
	*color = create_rgb((const char **)values);
	free_matrix(values);
	return (true);
}
