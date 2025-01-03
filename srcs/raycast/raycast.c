#include "../include/cub3D.h"

/**
 * @brief Casts a single ray for raycasting rendering.
 *
 * Calculates ray direction using camera plane, initializes ray parameters,
 * and performs DDA algorithm to find wall intersections.
 *
 * @param game Main game structure containing display info
 * @param player Player structure with position and camera data
 * @param x Screen x coordinate for which to cast the ray
 */
void	cast_ray(t_game *game, t_player *player, int x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		side;

	camera_x = 2 * x / (double)game->display.width - 1;
	ray_dir_x = player->camera.dir_x + player->camera.plane_x * camera_x;
	ray_dir_y = player->camera.dir_y + player->camera.plane_y * camera_x;
	init_ray(&player->camera, ray_dir_x, ray_dir_y, &player->pos);
	calculate_step_dist(&player->camera, &player->pos);
	side = perform_dda(game, &player->camera);
	if (side != -1)
	{
		player->camera.side = side;
		calculate_wall_dist(&player->camera, &player->pos, side);
	}
}

/**
 * @brief Initializes ray parameters for DDA algorithm.
 *
 * Sets ray direction vectors and calculates delta distances,
 * handling division by zero cases with large values.
 *
 * @param camera Camera structure to store ray parameters
 * @param ray_dir_x X component of ray direction
 * @param ray_dir_y Y component of ray direction
 * @param pos Current position in world space
 */
void	init_ray(t_camera *camera, double ray_dir_x, 
		double ray_dir_y, t_pos *pos)
{
	camera->ray_dir_x = ray_dir_x;
	camera->ray_dir_y = ray_dir_y;
	camera->map_x = (int)pos->x;
	camera->map_y = (int)pos->y;
	if (ray_dir_x == 0)
		camera->delta_dist_x = 1e30;
	else
		camera->delta_dist_x = fabs(1.0 / ray_dir_x);
	if (ray_dir_y == 0)
		camera->delta_dist_y = 1e30;
	else
		camera->delta_dist_y = fabs(1.0 / ray_dir_y);
}
