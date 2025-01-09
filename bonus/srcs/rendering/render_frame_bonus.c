/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:08:39 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 14:06:21 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	render_3d_view(t_game *game);
static void	init_frame_buffer(t_game *game, t_render_state *state);
static void	clear_frame_buffer(t_render_state *state, t_game *game);

/* Add this call in your frame update function */
int	render_frame(t_game *game)
{
	update_animations(game);
	if (game->changed)
	{
		render_3d_view(game);
		render_minimap(game);
		game->changed = false;
	}
	return (0);
}

/**
 * @brief Renders the 3D view of the game, including the floor,
 *  ceiling, and walls.
 *
 * This function initializes and clears the frame buffer,
 * renders the floor and ceiling,
 * then iterates over each column of the screen to render the walls.
 * Finally, it displays the image.
 *
 * @param game The game state used to access rendering and display parameters.
 * @param state The render state used to store the image data
 * during the rendering process.
 */
static void	render_3d_view(t_game *game)
{
	t_render_state	state;

	init_frame_buffer(game, &state);
	clear_frame_buffer(&state, game);
	render_3d_map(game, &state);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		state.img_ptr, 0, 0);
	mlx_destroy_image(game->mlx_ptr, state.img_ptr);
}

/**
 * @brief Initializes the frame buffer for rendering.
 *
 * This function creates a new image and sets up the necessary
 * data pointer for the frame buffer.
 *
 * @param game The game state that provides access to the display
 * dimensions and mlx pointer.
 * @param state The render state where the image pointer and data are stored.
 */
static void	init_frame_buffer(t_game *game, t_render_state *state)
{
	state->img_ptr = mlx_new_image(game->mlx_ptr,
			game->display.width, game->display.height);
	state->img_data = (int *)mlx_get_data_addr(state->img_ptr,
			&state->bits_per_pixel, &state->line_length, &state->endian);
}

/**
 * @brief Clears the frame buffer by setting all pixels to black.
 *
 * This function iterates through all pixels in the frame buffer
 * and sets their color to black
 *
 * @param state The render state containing the image data to be cleared.
 * @param game The game state used to access display dimensions.
 */
static void	clear_frame_buffer(t_render_state *state, t_game *game)
{
	int	total_pixels;
	int	i;

	total_pixels = game->display.width * game->display.height;
	i = 0;
	while (i < total_pixels)
	{
		state->img_data[i] = BLACK;
		i++;
	}
}
