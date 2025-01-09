/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:57:26 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 13:57:27 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

/**
* @brief Frees all allocated door textures and door array
*
* @param game The game structure containing door system data
*/
void	free_door_system(t_game *game)
{
	int	i;

	if (game->door_system.door)
		free(game->door_system.door);
	if (game->mlx_ptr)
	{
		i = 0;
		while (i < DOOR_FRAME)
		{
			if (game->door_system.texture[i])
				mlx_destroy_image(game->mlx_ptr, game->door_system.texture[i]);
			i++;
		}
	}
}
