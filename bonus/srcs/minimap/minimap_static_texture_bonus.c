#include "../../include/cub3D_bonus.h"

static void	create_static_background(t_render_state *state, 
								t_minimap *minimap);
static void create_static_walls(t_game *game, t_render_state *state, 
							t_minimap *minimap);
static void	draw_minimap_borders(t_render_state *state, t_minimap *minimap);

/**
* @brief Creates and initializes the static minimap texture
*
* @param game Game structure
* @return true if texture created successfully, false otherwise
*/
bool	init_static_minimap_texture(t_game *game)
{
	t_render_state	state;
	t_minimap		*minimap;

	minimap = &game->minimap;
	state.img_ptr = mlx_new_image(game->mlx_ptr, minimap->width, minimap->height);
	if (!state.img_ptr)
		return (false);
	state.img_data = (int *)mlx_get_data_addr(state.img_ptr, &state.bits_per_pixel,
											&state.line_length, &state.endian);
	if (!state.img_data)
	{
		mlx_destroy_image(game->mlx_ptr, state.img_ptr);
		return (false);
	}
	create_static_background(&state, minimap);
	draw_minimap_borders(&state, minimap);
	create_static_walls(game, &state, minimap);
	minimap->static_texture = state.img_ptr;
	minimap->texture_data = state.img_data;
	return (true);
}

/**
* @brief Creates the background layer of static texture
*
* @param game Game structure
* @param state Render state for pixel manipulation
* @param minimap Minimap structure with dimensions
*/
static void	create_static_background(t_render_state *state, 
								t_minimap *minimap)
{
	int x;
	int y;
	int *img;

	img = state->img_data;
	y = 0;
	while (y < minimap->height)
	{
		x = 0;
		while (x < minimap->width)
		{
			img[y * (state->line_length / 4) + x] = MINIMAP_BG_COLOR;
			x++;
		}
		y++;
	}
}

/**
* @brief Creates the walls layer of static texture
*
* @param game Game structure containing map data
* @param state Render state for pixel manipulation
* @param minimap Minimap structure
*/
static void create_static_walls(t_game *game, t_render_state *state, 
							t_minimap *minimap)
{
	int	map_x;
	int	map_y;
	int	pixel_x;
	int	pixel_y;
	int	*img;

	img = state->img_data;
	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < game->map.width)
		{
			if (game->map.matrix[map_y][map_x] == WALL)
			{
				pixel_y = map_y * minimap->tile_size + MINIMAP_BORDER_SIZE;
				while (pixel_y < (map_y + 1) * minimap->tile_size + MINIMAP_BORDER_SIZE)
				{
					pixel_x = map_x * minimap->tile_size + MINIMAP_BORDER_SIZE;
					while (pixel_x < (map_x + 1) * minimap->tile_size + MINIMAP_BORDER_SIZE)
					{
						img[pixel_y * (state->line_length / 4) + pixel_x] = MINIMAP_WALL_COLOR;
						pixel_x++;
					}
					pixel_y++;
				}
			}
			map_x++;
		}
		map_y++;
	}
}


/**
 * @brief Draws the border frame around the minimap
 *
 * @param state Pointer to the render state containing image data
 * @param minimap Pointer to minimap structure
 */
static void	draw_minimap_borders(t_render_state *state, t_minimap *minimap)
{
	int	i;

	i = 0;
	while (i < MINIMAP_BORDER_SIZE)
	{
		draw_horizontal_border(state, minimap, i);
		draw_horizontal_border(state, minimap, minimap->height - 1 - i);
		draw_vertical_border(state, minimap, i);
		draw_vertical_border(state, minimap, minimap->width - 1 - i);
		i++;
	}
}
