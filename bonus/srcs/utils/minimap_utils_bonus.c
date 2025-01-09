/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:57:54 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 13:57:55 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	destroy_minimap_texture(t_game *game)
{
	if (game->minimap.static_texture)
		mlx_destroy_image(game->mlx_ptr, game->minimap.static_texture);
}
