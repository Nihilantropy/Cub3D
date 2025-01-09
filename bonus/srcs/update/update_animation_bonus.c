/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:54:07 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 13:54:08 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

/**
 * @brief Updates all active door animations in the game
 *
 * Iterates through all doors in the game's door system. If a door
 * is marked as active, updates its animation and marks the game
 * state as changed to trigger a rerender.
 *
 * @param game Game structure containing door system data
 */
void	update_animations(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->door_system.door_counter)
	{
		if (game->door_system.door[i].active)
		{
			update_door_animation(game, &game->door_system.door[i]);
			game->changed = true;
		}
		i++;
	}
}
