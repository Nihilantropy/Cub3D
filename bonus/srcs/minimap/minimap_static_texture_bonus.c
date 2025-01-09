/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_static_texture_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:57:55 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 12:00:04 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	create_static_background(t_render_state *state,
				t_minimap *minimap);
static void	create_static_walls(t_game *game, t_render_state *state,
				t_minimap *minimap);
static void	draw_wall_tile(t_render_state *state, t_minimap *minimap,
				t_pos *tile_pos, int line_length);
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
	state.img_ptr = mlx_new_image(game->mlx_ptr,
			minimap->width, minimap->height);
	if (!state.img_ptr)
		return (false);
	state.img_data = (int *)mlx_get_data_addr(state.img_ptr,
			&state.bits_per_pixel, &state.line_length, &state.endian);
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
	int	x;
	int	y;
	int	*img;

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
* @brief Creates static wall textures for the minimap
*
* @param game Game structure containing map data
* @param state Render state for pixel manipulation
* @param minimap Minimap structure
*/
static void	create_static_walls(t_game *game, t_render_state *state,
							t_minimap *minimap)
{
	int		map_x;
	int		map_y;
	t_pos	tile_pos;

	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < game->map.width)
		{
			if (game->map.matrix[map_y][map_x] == WALL)
			{
				tile_pos.x = map_x;
				tile_pos.y = map_y;
				draw_wall_tile(state, minimap, &tile_pos, state->line_length);
			}
			map_x++;
		}
		map_y++;
	}
}

/**
* @brief Draws a single wall tile on the minimap
*
* @param state Render state containing image data
* @param minimap Minimap structure with dimensions
* @param tile_pos Structure containing map x,y coordinates
* @param line_length Length of image line in pixels
*/
static void	draw_wall_tile(t_render_state *state, t_minimap *minimap,
						t_pos *tile_pos, int line_length)
{
	int	pixel_x;
	int	pixel_y;
	int	start_y;
	int	*img;

	img = state->img_data;
	start_y = tile_pos->y * minimap->tile_size + MINIMAP_BORDER_SIZE;
	pixel_y = start_y;
	while (pixel_y < (tile_pos->y + 1) * minimap->tile_size
		+ MINIMAP_BORDER_SIZE)
	{
		pixel_x = tile_pos->x * minimap->tile_size + MINIMAP_BORDER_SIZE;
		while (pixel_x < (tile_pos->x + 1) * minimap->tile_size
			+ MINIMAP_BORDER_SIZE)
		{
			img[pixel_y * (line_length / 4) + pixel_x] = MINIMAP_WALL_COLOR;
			pixel_x++;
		}
		pixel_y++;
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
