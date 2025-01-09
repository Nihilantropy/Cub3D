/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door_system_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:55:10 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 15:40:06 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	init_door_system(t_game *game)
{
	game->door_system.texture = NULL;
	game->door_system.door = NULL;
	game->door_system.door_counter = 0;
}
