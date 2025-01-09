/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:28:09 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:36:30 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

# include "cub3D_bonus.h"

/* Minimap size and position constants */
# define MINIMAP_SCALE 0.2
# define MINIMAP_BORDER_SIZE 2
# define MINIMAP_PADDING 20
# define PLAYER_DOT_SIZE 4
# define FOV_LINE_LENGTH 15
# define FOV_ANGLE 60

typedef struct s_minimap
{
	int		width;
	int		height;
	int		pos_x;
	int		pos_y;
	int		tile_size;
	int		player_x;
	int		player_y;
	void	*static_texture;
	int		*texture_data;
}	t_minimap;

#endif
