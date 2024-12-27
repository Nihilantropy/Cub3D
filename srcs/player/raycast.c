#include "../include/cub3D.h"

/**
 * @brief Main ray casting function
 * Handles the complete ray casting process for the scene
 * Casts rays for each vertical screen line
 * 
 * @param game Game state containing all needed information
 * @param player Player struct containing position and direction
 */
void	cast_ray(t_game *game, t_player *player)
{
	int		x;
	double	camera_x;
	double	ray_angle;
	int		side;

	x = 0;
	while (x < game->display.width)
	{
		camera_x = 2 * x / (double)game->display.width - 1;
		ray_angle = player->rot.current_angle + atan2(camera_x, 1);
		init_ray(&player->camera, player, ray_angle);
		calculate_step_dist(&player->camera, player);
		side = perform_dda(game, &player->camera);
		calculate_wall_dist(&player->camera, side);
		draw_wall_stripe(game, x, (int)(game->display.height
				/ player->camera.perp_wall_dist));
		x++;
	}
}

/**
 * @brief Calculate the initial ray direction and position
 * Sets the initial values for ray direction and starting point
 * using player position and current ray angle
 * 
 * @param ray_info Structure containing ray calculation data
 * @param player Player information including position
 * @param ray_angle Current angle of the ray being cast
 */
void    init_ray(t_camera *ray_info, t_player *player, double ray_angle)
{
	ray_info->start_x = player->pos.x;
	ray_info->start_y = player->pos.y;
	ray_info->ray_dir_x = cos(ray_angle);
	ray_info->ray_dir_y = sin(ray_angle);
	ray_info->map_x = (int)player->pos.x;
	ray_info->map_y = (int)player->pos.y;
	ray_info->delta_dist_x = fabs(1 / ray_info->ray_dir_x);
	ray_info->delta_dist_y = fabs(1 / ray_info->ray_dir_y);
}

/**
 * @brief Calculate step direction and initial side distance
 * Determines which direction to step in the grid and how far
 * to initial wall intersection
 * 
 * @param ray_info Structure containing ray calculation data
 * @param player Player information
 */
void    calculate_step_dist(t_camera *ray_info, t_player *player)
{
    // Handle X direction
    if (ray_info->ray_dir_x < 0)
    {
        ray_info->step_x = -1;
        ray_info->side_dist_x = (player->pos.x - ray_info->map_x)
            * ray_info->delta_dist_x;
    }
    else
    {
        ray_info->step_x = 1;
        ray_info->side_dist_x = (ray_info->map_x + 1.0 - player->pos.x)
            * ray_info->delta_dist_x;
    }

    // Handle Y direction - careful with zero direction
    if (fabs(ray_info->ray_dir_y) < 1e-10)  // Nearly zero
    {
        ray_info->step_y = 0;
        ray_info->side_dist_y = INFINITY;
    }
    else if (ray_info->ray_dir_y < 0)
    {
        ray_info->step_y = -1;
        ray_info->side_dist_y = (player->pos.y - ray_info->map_y)
            * ray_info->delta_dist_y;
    }
    else
    {
        ray_info->step_y = 1;
        ray_info->side_dist_y = (ray_info->map_y + 1.0 - player->pos.y)
            * ray_info->delta_dist_y;
    }
}

/**
 * @brief Execute Digital Differential Analysis algorithm
 * Core of raycasting - finds wall hits using DDA algorithm
 * 
 * @param game Game state containing map information
 * @param ray_info Structure containing ray calculation data
 * @return int Returns 0 for vertical hit, 1 for horizontal hit
 */
int	perform_dda(t_game *game, t_camera *ray_info)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (ray_info->side_dist_x < ray_info->side_dist_y)
		{
			ray_info->side_dist_x += ray_info->delta_dist_x;
			ray_info->map_x += ray_info->step_x;
			side = 0;
		}
		else
		{
			ray_info->side_dist_y += ray_info->delta_dist_y;
			ray_info->map_y += ray_info->step_y;
			side = 1;
		}
		if (game->map.matrix[ray_info->map_y][ray_info->map_x] == WALL)
			hit = 1;
	}
	return (side);
}
