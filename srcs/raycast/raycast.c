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
		init_ray(&player->camera, ray_dir_x, ray_dir_y, &player->pos);
		calculate_step_dist(&player->camera, &player->pos);
		side = perform_dda(game, &player->camera);
		calculate_wall_dist(&player->camera, side);
		draw_wall_stripe(game, x, calculate_wall_height(game, 
			player->camera.perp_wall_dist));
		x++;
	}
}

void init_ray(t_camera *camera, double ray_dir_x, double ray_dir_y, t_pos *pos)
{
    // Explicitly set ray direction
    camera->ray_dir_x = ray_dir_x;
    camera->ray_dir_y = ray_dir_y;
    
    // Set initial map position based on player's position
    camera->map_x = (int)pos->x;
    camera->map_y = (int)pos->y;

    // Improved delta distance calculation
    camera->delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
    camera->delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);

    // Reset camera direction to avoid previous incorrect setting
    camera->dir_x = pos->x;
    camera->dir_y = pos->y;
}

void calculate_step_dist(t_camera *camera, t_pos *pos)
{
    // X-axis step and side distance
    if (camera->ray_dir_x < 0)
    {
        camera->step_x = -1;
        camera->side_dist_x = (pos->x - floor(pos->x)) * camera->delta_dist_x;
    }
    else
    {
        camera->step_x = 1;
        camera->side_dist_x = (ceil(pos->x) - pos->x) * camera->delta_dist_x;
    }

    // Y-axis step and side distance
    if (camera->ray_dir_y < 0)
    {
        camera->step_y = -1;
        camera->side_dist_y = (pos->y - floor(pos->y)) * camera->delta_dist_y;
    }
    else
    {
        camera->step_y = 1;
        camera->side_dist_y = (ceil(pos->y) - pos->y) * camera->delta_dist_y;
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
	int hit = 0;
	int side = -1;
	int max_iterations = game->map.width * game->map.height;  // Prevent infinite loops
	int iter = 0;

	while (hit == 0 && iter < max_iterations)
	{
		if (camera->side_dist_x < camera->side_dist_y)
		{
			camera->side_dist_x += camera->delta_dist_x;
			camera->map_x += camera->step_x;
			side = 0;  // X-side
		}
		else
		{
			camera->side_dist_y += camera->delta_dist_y;
			camera->map_y += camera->step_y;
			side = 1;  // Y-side
		}

		// Check for map boundaries and wall hit
		if (camera->map_x < 0 || camera->map_x >= game->map.width ||
			camera->map_y < 0 || camera->map_y >= game->map.height)
		{
			break;  // Out of map bounds
		}

		hit = (game->map.matrix[camera->map_y][camera->map_x] == WALL);
		iter++;
	}

	return (hit ? side : -1);  // Return -1 if no wall found
}

void calculate_wall_dist(t_camera *camera, int side)
{
    if (side == 0)  // X-side hit
    {
        // Calculate distance considering the player's fractional position
        double player_frac_x = camera->dir_x - floor(camera->dir_x);
        
        // If moving right, distance to wall is (1 - player_frac_x)
        // If moving left, distance is player_frac_x
        camera->perp_wall_dist = (camera->step_x > 0) 
            ? (1.0 - player_frac_x)
            : player_frac_x;
    }
    else  // Y-side hit
    {
        // Calculate distance considering the player's fractional position
        double player_frac_y = camera->dir_y - floor(camera->dir_y);
        
        // If moving up, distance is player_frac_y
        // If moving down, distance is (1 - player_frac_y)
        camera->perp_wall_dist = (camera->step_y < 0) 
            ? player_frac_y 
            : (1.0 - player_frac_y);
    }

    // Optional: Ensure result is non-negative and matches expected precision
    camera->perp_wall_dist = fabs(camera->perp_wall_dist);
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