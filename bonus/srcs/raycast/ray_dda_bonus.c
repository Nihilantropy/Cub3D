#include "../../include/cub3D_bonus.h"

static int	check_map_bounds(t_camera *camera, t_game *game);
static int	check_collision(t_game *game, t_camera *camera);
// static int	handle_door_collision(t_game *game, t_camera *camera, int side);
static void	perform_dda_step(t_camera *camera, int *side);


bool	handle_door_rendering(t_game *game, t_camera *camera, int side)
{
	t_door	*current_door;

	if (!(game->map.matrix[camera->map_y][camera->map_x] == DOOR))
		return (false);
	current_door = find_door_at_position(game, camera->map_x, camera->map_y);
	if (current_door)
	{
		if (current_door->is_rendering)
			return (false);
		camera->door_hit = true;
		camera->perp_door_dist = calculate_perp_dist(camera,
									&game->player.pos, side);
		camera->door_frame = current_door->frame;
		camera->door_side = side;
	}
	return (true);
}

/**
* @brief Performs DDA algorithm for raycasting
*
* @param game Game state containing map and camera data
* @param camera Camera containing ray information
* @return int Wall side hit or -1 if no hit
*/
int	perform_dda(t_game *game, t_camera *camera)
{
	int		hit;
	int		side;
	int		iter;

	hit = 0;
	side = -1;
	iter = 0;
	camera->door_hit = false;
	while (hit == 0 && iter < game->map.width * game->map.height)
	{
		perform_dda_step(camera, &side);
		if (check_map_bounds(camera, game) == -1)
			return (-1);
		handle_door_rendering(game, camera, side);
		hit = check_collision(game, camera);
		iter++;
	}
	camera->perp_wall_dist = calculate_perp_dist(camera, &game->player.pos, side);
	return (side);
}

/**
* @brief Checks if position is within map boundaries
*
* @param camera Camera containing position data
* @param game Game containing map dimensions
* @return int -1 if out of bounds, 0 if valid
*/
static int	check_map_bounds(t_camera *camera, t_game *game)
{
	if (camera->map_y < 0 || camera->map_y >= game->map.height ||
		camera->map_x < 0 || camera->map_x >= game->map.width)
		return (-1);
	return (0);
}

/**
* @brief Checks collision with walls and doors
*
* @param game Game state containing map data
* @param camera Camera data for ray
* @param side Current wall side hit
* @return int 1 if collision detected, 0 otherwise
*/
static int check_collision(t_game *game, t_camera *camera)
{
    if (game->map.matrix[camera->map_y][camera->map_x] == WALL)
    {
        camera->hit_type = WALL;
        return (1);
    }
    return (0);
}

/**
* @brief Handles door collision and state updates
*
* @param game Game state containing door data
* @param camera Camera data for ray calculations
* @param side Current wall side hit
* @return int 1 if closed door hit, 0 otherwise
*/
// static int	handle_door_collision(t_game *game, t_camera *camera, int side)
// {
// 	t_door	*door;

// 	door = find_door_at_position(game, camera->map_x, camera->map_y);
// 	if (!door)
// 		return (0);
// 	camera->door_hit = true;
// 	camera->door_frame = door->frame;
// 	camera->door_side = side;
// 	camera->perp_door_dist = calculate_perp_dist(camera, 
// 							&game->player.pos, side);
// 		return (0);
// 	return (0);
// }

/**
 * @brief Performs a single step in DDA algorithm.
 *
 * Updates ray position and side distances by stepping in either X or Y
 * direction depending on current side distances.
 *
 * @param camera Camera structure with ray and step info
 * @param side Pointer to store hit side (0 for X, 1 for Y)
 */
static void	perform_dda_step(t_camera *camera, int *side)
{
	if (camera->side_dist_x < camera->side_dist_y)
	{
		camera->side_dist_x += camera->delta_dist_x;
		camera->map_x += camera->step_x;
		*side = 0;
	}
	else
	{
		camera->side_dist_y += camera->delta_dist_y;
		camera->map_y += camera->step_y;
		*side = 1;
	}
}
