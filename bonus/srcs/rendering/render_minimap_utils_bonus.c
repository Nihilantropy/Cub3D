/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:08:43 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 13:52:11 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	draw_line(t_game *game, t_pos *start_point, int i);
static void	draw_mini_doors(t_game *game, t_pos *door_coord,
				t_minimap *minimap);

/**
* @brief Draws player position on minimap
*
* @param game Game structure containing player and minimap data
*/
void	draw_minimap_player(t_game *game, t_minimap *minimap)
{
	int	center_x;
	int	center_y;
	int	x;
	int	y;
	int	radius;

	center_x = minimap->pos_x
		+ (int)(game->player.pos.x * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	center_y = minimap->pos_y
		+ (int)(game->player.pos.y * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	radius = PLAYER_DOT_SIZE / 2;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_pixel_put(game->mlx_ptr, game->win_ptr,
					center_x + x, center_y + y, MINIMAP_PLAYER_COLOR);
			x++;
		}
		y++;
	}
}

/**
* @brief Draws FOV lines on minimap
*
* @param game Game structure containing player and camera data
*/
void	draw_player_fov(t_game *game, t_minimap *minimap)
{
	t_pos	start_point;
	int		i;

	start_point.x = minimap->pos_x
		+ (int)(game->player.pos.x * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	start_point.y = minimap->pos_y
		+ (int)(game->player.pos.y * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	i = 0;
	while (i < FOV_LINE_LENGTH)
	{
		draw_line(game, &start_point, i);
		i++;
	}
}

static void	draw_line(t_game *game, t_pos *start_point, int i)
{
	t_pos	line_point;
	double	angle;

	angle = atan2(game->player.camera.dir_y, game->player.camera.dir_x);
	line_point.x = cos(angle) * i;
	line_point.y = sin(angle) * i;
	mlx_pixel_put(game->mlx_ptr, game->win_ptr,
		start_point->x + (int)line_point.x, start_point->y
		+ (int)line_point.y, MINIMAP_FOV_COLOR);
	line_point.x = cos(angle - FOV_ANGLE * M_PI / 360.0) * i;
	line_point.y = sin(angle - FOV_ANGLE * M_PI / 360.0) * i;
	mlx_pixel_put(game->mlx_ptr, game->win_ptr,
		start_point->x + (int)line_point.x, start_point->y
		+ (int)line_point.y, MINIMAP_FOV_COLOR);
	line_point.x = cos(angle + FOV_ANGLE * M_PI / 360.0) * i;
	line_point.y = sin(angle + FOV_ANGLE * M_PI / 360.0) * i;
	mlx_pixel_put(game->mlx_ptr, game->win_ptr,
		start_point->x + (int)line_point.x, start_point->y
		+ (int)line_point.y, MINIMAP_FOV_COLOR);
}

/**
* @brief Draws doors on minimap
*
* @param game Game structure containing door system data
*/
void	draw_minimap_door(t_game *game, t_minimap *minimap)
{
	t_pos	door_coord;
	int		i;

	i = 0;
	while (i < game->door_system.door_counter)
	{
		door_coord.x = game->minimap.pos_x
			+ (int)(game->door_system.door[i].pos.x * minimap->tile_size)
			+ MINIMAP_BORDER_SIZE;
		door_coord.y = game->minimap.pos_y
			+ (int)(game->door_system.door[i].pos.y * minimap->tile_size)
			+ MINIMAP_BORDER_SIZE;
		draw_mini_doors(game, &door_coord, minimap);
		i++;
	}
}

static void	draw_mini_doors(t_game *game, t_pos *door_coord, t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->tile_size)
	{
		x = 0;
		while (x < game->minimap.tile_size)
		{
			mlx_pixel_put(game->mlx_ptr, game->win_ptr,
				door_coord->x + x, door_coord->y + y, MINIMAP_DOOR_COLOR);
			x++;
		}
		y++;
	}
}
