#include "../../include/cub3D_bonus.h"

/**
* @brief Draws player position on minimap
*
* @param game Game structure containing player and minimap data
*/
void    draw_minimap_player(t_game *game, t_minimap *minimap)
{
	int	center_x;
	int	center_y;
	int	x;
	int	y;
	int	radius;

	center_x = minimap->pos_x + 
		(int)(game->player.pos.x * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	center_y = minimap->pos_y + 
		(int)(game->player.pos.y * minimap->tile_size) + MINIMAP_BORDER_SIZE;
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
void    draw_player_fov(t_game *game, t_minimap *minimap)
{
	int     start_x;
	int     start_y;
	double  angle;
	int     i;
	double  dx, dy;

	start_x = minimap->pos_x + 
		(int)(game->player.pos.x * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	start_y = minimap->pos_y + 
		(int)(game->player.pos.y * minimap->tile_size) + MINIMAP_BORDER_SIZE;

	angle = atan2(game->player.camera.dir_y, game->player.camera.dir_x);
	i = 0;
	while (i < FOV_LINE_LENGTH)
	{
		dx = cos(angle) * i;
		dy = sin(angle) * i;
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			start_x + (int)dx, start_y + (int)dy, MINIMAP_FOV_COLOR);
		dx = cos(angle - FOV_ANGLE * M_PI / 360.0) * i;
		dy = sin(angle - FOV_ANGLE * M_PI / 360.0) * i;
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			start_x + (int)dx, start_y + (int)dy, MINIMAP_FOV_COLOR);
		dx = cos(angle + FOV_ANGLE * M_PI / 360.0) * i;
		dy = sin(angle + FOV_ANGLE * M_PI / 360.0) * i;
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			start_x + (int)dx, start_y + (int)dy, MINIMAP_FOV_COLOR);
		i++;
	}
}

/**
* @brief Draws doors on minimap
*
* @param game Game structure containing door system data
*/
void    draw_minimap_door(t_game *game, t_minimap *minimap)
{
	int	door_x;
	int	door_y;
	int	x;
	int	y;
	int	i;

	i = 0;
	while (i < game->door_system.door_counter)
	{
		door_x = game->minimap.pos_x + 
			(int)(game->door_system.door[i].pos.x * minimap->tile_size) + 
			MINIMAP_BORDER_SIZE;
		door_y = game->minimap.pos_y + 
			(int)(game->door_system.door[i].pos.y * minimap->tile_size) + 
			MINIMAP_BORDER_SIZE;
		y = 0;
		while (y < minimap->tile_size)
		{
			x = 0;
			while (x < game->minimap.tile_size)
			{
				mlx_pixel_put(game->mlx_ptr, game->win_ptr,
					door_x + x, door_y + y, MINIMAP_DOOR_COLOR);
				x++;
			}
			y++;
		}
		i++;
	}
}