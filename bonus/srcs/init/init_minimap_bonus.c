/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:55:15 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:55:16 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	init_minimap(t_game *game)
{
	game->minimap.width = 0;
	game->minimap.height = 0;
	game->minimap.pos_x = 0;
	game->minimap.pos_y = 0;
	game->minimap.tile_size = 0;
	game->minimap.player_x = 0;
	game->minimap.player_y = 0;
	game->minimap.static_texture = NULL;
	game->minimap.texture_data = NULL;
}
