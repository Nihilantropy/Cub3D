/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_static_texture_utils_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:57:57 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:57:58 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

/**
 * @brief Draws horizontal borders of the minimap
 *
 * @param state Pointer to the render state containing image data
 * @param minimap Pointer to minimap structure
 * @param y Y position to draw border
 */
void	draw_horizontal_border(t_render_state *state, t_minimap *minimap,
			int y)
{
	int	x;
	int	*img;

	img = state->img_data;
	x = 0;
	while (x < minimap->width)
	{
		img[y * (state->line_length / 4) + x] = MINIMAP_BORDER_COLOR;
		x++;
	}
}

/**
 * @brief Draws vertical borders of the minimap
 *
 * @param state Pointer to the render state containing image data
 * @param minimap Pointer to minimap structure
 * @param x X position to draw border
 */
void	draw_vertical_border(t_render_state *state, t_minimap *minimap,
			int x)
{
	int	y;
	int	*img;

	img = state->img_data;
	y = 0;
	while (y < minimap->height)
	{
		img[y * (state->line_length / 4) + x] = MINIMAP_BORDER_COLOR;
		y++;
	}
}
