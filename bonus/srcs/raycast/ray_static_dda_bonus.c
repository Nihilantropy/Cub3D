#include "../../include/cub3D_bonus.h"

static int	check_static_collision(t_game *game, t_camera *camera);

/**
* @brief Performs DDA algorithm for raycasting
*
* @param game Game state containing map and camera data
* @param camera Camera containing ray information
* @return int Wall side hit or -1 if no hit
*/
int	perform_static_dda(t_game *game, t_camera *camera)
{
	int		hit;
	int		side;
	int		iter;

	hit = 0;
	side = -1;
	iter = 0;
	while (hit == 0 && iter < game->map.width * game->map.height)
	{
		perform_dda_step(camera, &side);
		if (check_map_bounds(camera, game) == -1)
			return (-1);
		hit = check_static_collision(game, camera);
		iter++;
	}
	if (hit == 0)
		return (-1);
	camera->perp_dist = calculate_perp_dist(camera, &game->player.pos, side);
	return (side);
}

/**
* @brief Checks collision with walls and doors
*
* @param game Game state containing map data
* @param camera Camera data for ray
* @param side Current wall side hit
* @return int 1 if collision detected, 0 otherwise
*/
static int	check_static_collision(t_game *game, t_camera *camera)
{
	t_door	*door;

	door = NULL;
	if (game->map.matrix[camera->map_y][camera->map_x] == WALL)
	{
		camera->hit_obj = e_wall;
		return (1);
	}
	else if (game->map.matrix[camera->map_y][camera->map_x] == DOOR)
	{
		door = find_door_at_position(game, camera->map_x, camera->map_y);
		if (door)
		{
			if (door->anim_state == door_closed)
			{
				camera->hit_obj = e_door;
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}
