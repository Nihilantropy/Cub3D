/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_state_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:50:20 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:50:21 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

bool	player_on_door_pos(t_player *player, t_door *door)
{
	if ((int)player->pos.y == (int)door->pos.y
		&& (int)player->pos.x == (int)door->pos.x)
		return (true);
	return (false);
}
