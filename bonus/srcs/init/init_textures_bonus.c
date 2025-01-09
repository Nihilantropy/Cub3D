/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:55:19 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:56:53 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	init_textures(t_game *game)
{
	game->textures.east = NULL;
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.floor_color = 0;
	game->textures.ceiling_color = 0;
	game->textures.floor = NULL;
	game->textures.ceiling = NULL;
	game->textures.size = 0;
}
