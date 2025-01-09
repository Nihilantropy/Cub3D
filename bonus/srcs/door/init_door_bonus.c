/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:50:22 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 13:33:18 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	init_doors(t_game *game)
{
	int	i;

	game->door_system.door = malloc(sizeof(t_door)
			* game->door_system.door_counter);
	if (!game->door_system.door)
		ft_exit_error(ERR_ALLOC_DOOR);
	i = 0;
	while (i < game->door_system.door_counter)
	{
		game->door_system.door[i].pos.x = 0;
		game->door_system.door[i].pos.y = 0;
		game->door_system.door[i].frame = 0;
		game->door_system.door[i].anim_counter = 0;
		game->door_system.door[i].anim_state = door_closed;
		game->door_system.door[i].active = false;
		game->door_system.door[i].id = i + 1;
		game->door_system.door[i].interaction.coord_dist.x = 0.0;
		game->door_system.door[i].interaction.coord_dist.y = 0.0;
		game->door_system.door[i].interaction.distance = 0.0;
		i++;
	}
}
