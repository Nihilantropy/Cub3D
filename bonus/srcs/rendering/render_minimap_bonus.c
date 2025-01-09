/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:08:42 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 12:08:43 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	draw_static_texture(t_game *game, t_minimap *minimap);
static void	draw_dynamic_texture(t_game *game, t_minimap *minimap);

/**
* @brief Main rendering function for the minimap
*
* Creates a new image for the minimap, draws static texture first,
* then overlays dynamic elements (player, doors, FOV)
*
* @param game Pointer to the main game structure
*/
void	render_minimap(t_game *game)
{
	t_minimap		*minimap;

	minimap = &game->minimap;
	draw_static_texture(game, minimap);
	draw_dynamic_texture(game, minimap);
}

/**
* @brief Renders the static (pre-rendered) minimap texture
*
* @param game Game structure containing MLX data
* @param minimap Minimap structure containing static texture
*/
static void	draw_static_texture(t_game *game, t_minimap *minimap)
{
	if (minimap->static_texture)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			minimap->static_texture, minimap->pos_x, minimap->pos_y);
}

/**
* @brief Renders dynamic elements of the minimap
*
* @param game Game structure containing game state
* @param state Render state containing image data
* @param minimap Minimap structure with dimensions
*/
static void	draw_dynamic_texture(t_game *game, t_minimap *minimap)
{
	draw_minimap_door(game, minimap);
	draw_minimap_player(game, minimap);
	draw_player_fov(game, minimap);
}
