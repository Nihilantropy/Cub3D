/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:08:37 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 14:05:08 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	fill_horizontal_line(t_render_state *state, int y,
				int width, int color);

/**
 * @brief Renders the floor and ceiling of the game display.
 *
 * The function fills the top half of the screen with the ceiling color and
 * the bottom half with the floor color.
 *
 * @param game The game state containing display and texture information.
 * @param state The current rendering state.
 */
void	render_floor_ceiling(t_game *game, t_render_state *state)
{
	int	y;
	int	half_height;

	half_height = game->display.height / 2;
	y = 0;
	while (y < half_height)
	{
		fill_horizontal_line(state, y, game->display.width,
			game->textures.ceiling_color);
		y++;
	}
	while (y < game->display.height)
	{
		fill_horizontal_line(state, y, game->display.width,
			game->textures.floor_color);
		y++;
	}
}

/**
 * @brief Fills a horizontal line in the render state with a specified color.
 *
 * This function sets the color of each pixel in the given row.
 *
 * @param state The current rendering state.
 * @param y The row (y-coordinate) to fill.
 * @param width The width of the screen.
 * @param color The color to set for the pixels in the row.
 */
static void	fill_horizontal_line(t_render_state *state, int y,
							int width, int color)
{
	int	x;

	x = 0;
	while (x < width)
	{
		state->img_data[y * width + x] = color;
		x++;
	}
}
