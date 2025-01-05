#include "../../include/cub3D_bonus.h"

static void	draw_fov_line(t_game *game, t_render_state *state, 
				t_minimap *minimap, double angle);

/**
 * @brief Draws the walls on the minimap
 *
 * @param game Game structure containing map data
 * @param state Render state for drawing
 * @param minimap Minimap structure with dimensions
 */
void	draw_minimap_walls(t_game *game, t_render_state *state, t_minimap *minimap)
{
	int	map_x;
	int	map_y;
	int	pixel_x;
	int	pixel_y;
	int	*img;

	img = state->img_data;
	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < game->map.width)
		{
			if (game->map.matrix[map_y][map_x] == WALL)
			{
				pixel_y = map_y * minimap->tile_size + MINIMAP_BORDER_SIZE;
				while (pixel_y < (map_y + 1) * minimap->tile_size + MINIMAP_BORDER_SIZE)
				{
					pixel_x = map_x * minimap->tile_size + MINIMAP_BORDER_SIZE;
					while (pixel_x < (map_x + 1) * minimap->tile_size + MINIMAP_BORDER_SIZE)
					{
						img[pixel_y * (state->line_length / 4) + pixel_x] = MINIMAP_WALL_COLOR;
						pixel_x++;
					}
					pixel_y++;
				}
			}
			map_x++;
		}
		map_y++;
	}
}

/**
 * @brief Draws the player dot on the minimap
 *
 * @param game Game structure containing player position
 * @param state Render state for drawing
 * @param minimap Minimap structure with dimensions
 */
void	draw_minimap_player(t_game *game, t_render_state *state, t_minimap *minimap)
{
	int	pixel_x;
	int	pixel_y;
	int	start_x;
	int	start_y;
	int	*img;

	img = state->img_data;
	start_x = (int)(game->player.pos.x * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	start_y = (int)(game->player.pos.y * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	pixel_y = start_y - PLAYER_DOT_SIZE / 2;
	while (pixel_y < start_y + PLAYER_DOT_SIZE / 2)
	{
		pixel_x = start_x - PLAYER_DOT_SIZE / 2;
		while (pixel_x < start_x + PLAYER_DOT_SIZE / 2)
		{
			if (pixel_x >= 0 && pixel_x < minimap->width &&
				pixel_y >= 0 && pixel_y < minimap->height)
				img[pixel_y * (state->line_length / 4) + pixel_x] = MINIMAP_PLAYER_COLOR;
			pixel_x++;
		}
		pixel_y++;
	}
}

/**
 * @brief Draws the player's field of view on the minimap
 *
 * @param game Game structure containing player direction
 * @param state Render state for drawing
 * @param minimap Minimap structure with dimensions
 */
void	draw_player_fov(t_game *game, t_render_state *state, t_minimap *minimap)
{
	double	player_angle;
	double	fov_start;
	double	fov_end;

	player_angle = atan2(game->player.camera.dir_y, game->player.camera.dir_x);
	fov_start = player_angle - (FOV_ANGLE * M_PI / 360.0);
	fov_end = player_angle + (FOV_ANGLE * M_PI / 360.0);
	draw_fov_line(game, state, minimap, player_angle);
	draw_fov_line(game, state, minimap, fov_start);
	draw_fov_line(game, state, minimap, fov_end);
}

void	draw_minimap_door(t_game *game, t_render_state *state, t_minimap *minimap)
{
	int	map_x;
	int	map_y;
	int	pixel_x;
	int	pixel_y;
	int	*img;

	img = state->img_data;
	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < game->map.width)
		{
			if (game->map.matrix[map_y][map_x] == DOOR)
			{
				pixel_y = map_y * minimap->tile_size + MINIMAP_BORDER_SIZE;
				while (pixel_y < (map_y + 1) * minimap->tile_size + MINIMAP_BORDER_SIZE)
				{
					pixel_x = map_x * minimap->tile_size + MINIMAP_BORDER_SIZE;
					while (pixel_x < (map_x + 1) * minimap->tile_size + MINIMAP_BORDER_SIZE)
					{
						img[pixel_y * (state->line_length / 4) + pixel_x] = MINIMAP_DOOR_COLOR;
						pixel_x++;
					}
					pixel_y++;
				}
			}
			map_x++;
		}
		map_y++;
	}
}

static void	draw_fov_line(t_game *game, t_render_state *state, 
				t_minimap *minimap, double angle)
{
	int		i;
	int		start_x;
	int		start_y;
	int		x;
	int		y;

	start_x = (int)(game->player.pos.x * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	start_y = (int)(game->player.pos.y * minimap->tile_size) + MINIMAP_BORDER_SIZE;
	i = 0;
	while (i < FOV_LINE_LENGTH)
	{
		x = start_x + (int)(cos(angle) * i);
		y = start_y + (int)(sin(angle) * i);
		if (x >= 0 && x < minimap->width && y >= 0 && y < minimap->height)
			state->img_data[y * (state->line_length / 4) + x] = MINIMAP_FOV_COLOR;
		i++;
	}
}
