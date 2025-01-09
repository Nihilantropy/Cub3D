/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:27:57 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:36:04 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_BONUS_H
# define COLORS_BONUS_H

# define RED 0xFF0000
# define YELLOW 0xFFFF00
# define GREEN 0x00FF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GRAY 0xAAAAAA

/* mlx handle None param in xpm file as fully opaque black */
# define TRANSPARENT 0xFF000000

/* Minimap colors with alpha channel (ARGB format) */
# define MINIMAP_WALL_COLOR     0xFF666666
# define MINIMAP_DOOR_COLOR     0x00AF0000
# define MINIMAP_FLOOR_COLOR    0xFF333333
# define MINIMAP_PLAYER_COLOR   0xFFFF0000
# define MINIMAP_FOV_COLOR      0xFFFFFF00
# define MINIMAP_BORDER_COLOR   0xFFFFFFFF
# define MINIMAP_BG_COLOR       0xAA000000

#endif
