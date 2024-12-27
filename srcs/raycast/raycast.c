#include "../include/cub3D.h"

void	cast_ray(t_game *game, t_player *player)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		side;

	x = 0;
	while (x < game->display.width)
	{
		camera_x = 2 * x / (double)game->display.width - 1;
		ray_dir_x = player->camera.dir_x + player->camera.plane_x * camera_x;
		ray_dir_y = player->camera.dir_y + player->camera.plane_y * camera_x;
		init_ray(&player->camera, ray_dir_x, ray_dir_y);
		calculate_step_dist(&player->camera, &player->pos);
		side = perform_dda(game, &player->camera);
		calculate_wall_dist(&player->camera, side);
		draw_wall_stripe(game, x, calculate_wall_height(game, 
			player->camera.perp_wall_dist));
		x++;
	}
}

void	init_ray(t_camera *camera, double ray_dir_x, double ray_dir_y)
{
	camera->ray_dir_x = ray_dir_x;
	camera->ray_dir_y = ray_dir_y;
	camera->map_x = (int)camera->dir_x;
	camera->map_y = (int)camera->dir_y;
	if (camera->ray_dir_x == 0)
		camera->delta_dist_x = 1e30;
	else
		camera->delta_dist_x = fabs(1 / camera->ray_dir_x);
	if (camera->ray_dir_y == 0)
		camera->delta_dist_y = 1e30;
	else
		camera->delta_dist_y = fabs(1 / camera->ray_dir_y);
}

void	calculate_step_dist(t_camera *camera, t_pos *pos)
{
	if (camera->ray_dir_x < 0)
	{
		camera->step_x = -1;
		camera->side_dist_x = (pos->x - camera->map_x)
			* camera->delta_dist_x;
	}
	else
	{
		camera->step_x = 1;
		camera->side_dist_x = (camera->map_x + 1.0 - pos->x)
			* camera->delta_dist_x;
	}
	set_y_step_dist(camera, pos);
}

void	set_y_step_dist(t_camera *camera, t_pos *pos)
{
	if (camera->ray_dir_y < 0)
	{
		camera->step_y = -1;
		camera->side_dist_y = (pos->y - camera->map_y)
			* camera->delta_dist_y;
	}
	else
	{
		camera->step_y = 1;
		camera->side_dist_y = (camera->map_y + 1.0 - pos->y)
			* camera->delta_dist_y;
	}
}

int	step_in_x_direction(t_camera *camera)
{
	camera->side_dist_x += camera->delta_dist_x;
	camera->map_x += camera->step_x;
	return (0);
}

int	step_in_y_direction(t_camera *camera)
{
	camera->side_dist_y += camera->delta_dist_y;
	camera->map_y += camera->step_y;
	return (1);
}

int	check_wall_hit(t_game *game, t_camera *camera)
{
	if (camera->map_y < 0 || camera->map_x < 0
		|| camera->map_y >= game->map.height
		|| camera->map_x >= game->map.width)
		return (1);
	return (game->map.matrix[camera->map_y][camera->map_x] == WALL);
}

int	perform_dda(t_game *game, t_camera *camera)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (camera->side_dist_x < camera->side_dist_y)
			side = step_in_x_direction(camera);
		else
			side = step_in_y_direction(camera);
		hit = check_wall_hit(game, camera);
	}
	return (side);
}

void	calculate_wall_dist(t_camera *camera, int side)
{
	if (side == 0)
		camera->perp_wall_dist = (camera->map_x - camera->dir_x
			+ (1 - camera->step_x) / 2) / camera->ray_dir_x;
	else
		camera->perp_wall_dist = (camera->map_y - camera->dir_y
			+ (1 - camera->step_y) / 2) / camera->ray_dir_y;
}

int	calculate_wall_height(t_game *game, double perp_wall_dist)
{
	int	line_height;
	int	max_height;

	max_height = game->display.height;
	line_height = (int)(max_height / perp_wall_dist);
	if (line_height > max_height)
		return (max_height);
	return (line_height);
}

void	draw_wall_stripe(t_game *game, int x, int wall_height)
{
	int	draw_start;
	int	draw_end;
	int	mid_point;

	mid_point = game->display.height / 2;
	draw_start = -wall_height / 2 + mid_point;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = wall_height / 2 + mid_point;
	if (draw_end >= game->display.height)
		draw_end = game->display.height - 1;
	(void)x;
	// draw_vertical_line(game, x, draw_start, draw_end);
}