/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:01 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 15:53:39 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_BONUS_H
# define DOOR_BONUS_H

# include "cub3D_bonus.h"

# define DOOR_FRAME 30
# define DOOR_ANIM_SPEED 1

# define DOOR_TEXTURE_1 "./texture/door/door_texture_1.xpm"
# define DOOR_TEXTURE_2 "./texture/door/door_texture_2.xpm"
# define DOOR_TEXTURE_3 "./texture/door/door_texture_3.xpm"
# define DOOR_TEXTURE_4 "./texture/door/door_texture_4.xpm"
# define DOOR_TEXTURE_5 "./texture/door/door_texture_5.xpm"
# define DOOR_TEXTURE_6 "./texture/door/door_texture_6.xpm"

typedef enum e_door_state
{
	door_closed = 0,
	door_opening,
	door_open,
	door_closing
}	t_door_state;

typedef struct s_door_inter
{
	t_pos	coord_dist;
	double	distance;
}	t_door_inter;

typedef struct s_door
{
	t_pos			pos;
	t_door_state	anim_state;
	t_door_inter	interaction;
	int				frame;
	int				anim_counter;
	bool			active;
	int				id;
}	t_door;

typedef struct s_door_system
{
	void	**texture;
	t_door	*door;
	int		door_counter;
}	t_door_system;

#endif
