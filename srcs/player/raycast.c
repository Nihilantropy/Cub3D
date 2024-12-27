// #include "../include/cub3D.h"

// /**
//  * @brief Main ray casting function
//  * Handles the complete ray casting process for the scene
//  * Casts rays for each vertical screen line
//  * 
//  * @param game Game state containing all needed information
//  * @param player Player struct containing position and direction
//  */
// void	cast_ray(t_game *game, t_player *player)
// {
// 	int		x;
// 	double	camera_x;
// 	double	ray_angle;
// 	int		side;

// 	x = 0;
// 	while (x < game->display.width)
// 	{
// 		camera_x = 2 * x / (double)game->display.width - 1;
// 		ray_angle = player->rot.current_angle + atan2(camera_x, 1);
// 		init_ray(&player->camera, player, ray_angle);
// 		calculate_step_dist(&player->camera, player);
// 		side = perform_dda(game, &player->camera);
// 		calculate_wall_dist(&player->camera, side);
// 		draw_wall_stripe(game, x, calculate_wall_height(game, 
// 			player->camera.perp_wall_dist));
// 		x++;
// 	}
// }

// /**
//  * @brief Calculate the initial ray direction and position
//  * Sets the initial values for ray direction and starting point
//  * using player position and current ray angle
//  * 
//  * @param ray_info Structure containing ray calculation data
//  * @param player Player information including position
//  * @param ray_angle Current angle of the ray being cast
//  */
// void	init_ray(t_camera *ray_info, t_player *player, double ray_angle)
// {
// 	ray_info->start_x = player->pos.x;
// 	ray_info->start_y = player->pos.y;
// 	ray_info->ray_dir_x = cos(ray_angle);
// 	ray_info->ray_dir_y = sin(ray_angle);
// 	ray_info->map_x = (int)player->pos.x;
// 	ray_info->map_y = (int)player->pos.y;
// 	ray_info->delta_dist_x = fabs(1 / ray_info->ray_dir_x);
// 	ray_info->delta_dist_y = fabs(1 / ray_info->ray_dir_y);
// }

// /**
//  * @brief Calculate step direction and initial side distance
//  * Determines which direction to step in the grid and how far
//  * to initial wall intersection
//  * 
//  * @param ray_info Structure containing ray calculation data
//  * @param player Player information
//  */
// void	calculate_step_dist(t_camera *ray_info, t_player *player)
// {
// 	if (ray_info->ray_dir_x < 0)
// 	{
// 		ray_info->step_x = -1;
// 		ray_info->side_dist_x = (player->pos.x - ray_info->map_x)
// 			* ray_info->delta_dist_x;
// 	}
// 	else
// 	{
// 		ray_info->step_x = 1;
// 		ray_info->side_dist_x = (ray_info->map_x + 1.0 - player->pos.x)
// 			* ray_info->delta_dist_x;
// 	}
// 	set_y_step_dist(ray_info, player);
// }

// void	set_y_step_dist(t_camera *ray_info, t_player *player)
// {
// 	if (fabs(ray_info->ray_dir_y) < 1e-10)
// 	{
// 		ray_info->step_y = 0;
// 		ray_info->side_dist_y = INFINITY;
// 		return ;
// 	}
// 	if (ray_info->ray_dir_y < 0)
// 	{
// 		ray_info->step_y = -1;
// 		ray_info->side_dist_y = (player->pos.y - ray_info->map_y)
// 			* ray_info->delta_dist_y;
// 	}
// 	else
// 	{
// 		ray_info->step_y = 1;
// 		ray_info->side_dist_y = (ray_info->map_y + 1.0 - player->pos.y)
// 			* ray_info->delta_dist_y;
// 	}
// }

// /**
//  * @brief Execute Digital Differential Analysis algorithm
//  * Core of raycasting - finds wall hits using DDA algorithm
//  * 
//  * @param game Game state containing map information
//  * @param ray_info Structure containing ray calculation data
//  * @return int Returns 0 for vertical hit, 1 for horizontal hit
//  */
// int	perform_dda(t_game *game, t_camera *ray_info)
// {
// 	int	hit;
// 	int	side;

// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		if (ray_info->side_dist_x < ray_info->side_dist_y)
// 			side = step_in_x_direction(ray_info);
// 		else
// 			side = step_in_y_direction(ray_info);
// 		if (check_wall_hit(game, ray_info))
// 			hit = 1;
// 	}
// 	return (side);
// }

// int	step_in_x_direction(t_camera *ray_info)
// {
// 	ray_info->side_dist_x += ray_info->delta_dist_x;
// 	ray_info->map_x += ray_info->step_x;
// 	return (0);
// }



// void	calculate_wall_dist(t_camera *ray_info, int side)
// {
// 	if (side == 0)
// 		ray_info->perp_wall_dist = (ray_info->map_x - ray_info->start_x
// 			+ (1 - ray_info->step_x) / 2) / ray_info->ray_dir_x;
// 	else
// 		ray_info->perp_wall_dist = (ray_info->map_y - ray_info->start_y
// 			+ (1 - ray_info->step_y) / 2) / ray_info->ray_dir_y;
// }

// int	calculate_wall_height(t_game *game, double perp_wall_dist)
// {
// 	int	line_height;

// 	line_height = (int)(game->display.height / perp_wall_dist);
// 	if (line_height > game->display.height)
// 		return (game->display.height);
// 	return (line_height);
// }

// void	draw_wall_stripe(t_game *game, int x, int wall_height)
// {
// 	int	draw_start;
// 	int	draw_end;

// 	draw_start = -wall_height / 2 + game->display.height / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = wall_height / 2 + game->display.height / 2;
// 	if (draw_end >= game->display.height)
// 		draw_end = game->display.height - 1;
// 	draw_vertical_line(game, x, draw_start, draw_end);
// }

// #define WALL_COLOR 0xFFFFFF
// #define FLOOR_COLOR 0x808080
// #define CEILING_COLOR 0x4040FF

// void	draw_vertical_line(t_game *game, int x, int start, int end)
// {
// 	int	y;

// 	y = 0;
// 	while (y < start)
// 		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y++, CEILING_COLOR);
// 	while (y < end)
// 		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y++, WALL_COLOR);
// 	while (y < game->display.height)
// 		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x, y++, FLOOR_COLOR);
// }