/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:08:45 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 14:00:12 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

/**
 * @brief Renders a textured wall slice to the screen.
 *
 * This function applies the texture to a wall slice
 * and renders it onto the display
 * based on the calculated texture position.
 *
 * @param state The render state that holds the image data to be modified.
 * @param slice The wall slice to be rendered.
 * @param game The game state to access display parameters.
 * @param x The x-coordinate of the current slice on the screen.
 * @return None.
 */
void	render_textured_slice(t_render_state *state, t_slice *slice,
									t_game *game, int x)
{
	int				y;
	double			step;
	double			tex_pos;
	t_render_state	tex_data;

	if (!init_texture_rendering(slice, &tex_data, &step))
		return ;
	tex_pos = (slice->start_y - game->display.height / 2
			+ slice->height / 2) * step;
	y = slice->start_y;
	while (y < slice->end_y)
	{
		get_texture_color(state, &tex_data, slice,
			TEXTURE_SIZE * ((int)tex_pos & (TEXTURE_SIZE - 1))
			+ slice->tex_x);
		if (y * game->display.width + x >= 0
			&& y * game->display.width + x < game->display.width
			* game->display.height)
			state->img_data[y * game->display.width + x] = state->color;
		tex_pos += step;
		y++;
	}
}

/**
 * @brief Initializes rendering parameters for wall textures.
 *
 * Gets texture data and calculates texture mapping step size.
 *
 * @param slice The wall slice containing texture information.
 * @param tex_data Structure to store the texture rendering data.
 * @param step Calculated step size for texture mapping.
 * @return True if initialization succeeds, false otherwise.
 */
bool	init_texture_rendering(t_slice *slice, t_render_state *tex_data,
								double *step)
{
	if (!get_texture_data(slice, tex_data))
		return (false);
	*step = 1.0 * TEXTURE_SIZE / slice->height;
	return (true);
}

/**
 * @brief Retrieves texture data for a wall slice.
 *
 * This function extracts the texture data for the given wall slice
 * and handles errors if the texture
 * is null or retrieval fails.
 *
 * @param slice The wall slice containing the texture information.
 * @param tex_data A pointer to a t_render_state structure to
 * store the texture data.
 * @return True if the texture data was successfully retrieved, otherwise false.
 */
bool	get_texture_data(t_slice *slice, t_render_state *tex_data)
{
	if (!slice->texture)
	{
		ft_putstr_fd(ERR_SLICE_TEXTURE, 2);
		return (false);
	}
	tex_data->img_data = (int *)mlx_get_data_addr(slice->texture,
			&tex_data->bits_per_pixel, &tex_data->line_length,
			&tex_data->endian);
	if (!tex_data->img_data)
	{
		ft_putstr_fd(ERR_GET_TEXTURE_DATA, 2);
		return (false);
	}
	return (true);
}
