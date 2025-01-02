#include "../include/cub3D.h"

int	check_wall_hit(t_game *game, t_camera *camera)
{
	if (camera->map_y < 0 || camera->map_x < 0
		|| camera->map_y >= game->map.height
		|| camera->map_x >= game->map.width)
		return (1);
	return (game->map.matrix[camera->map_y][camera->map_x] == WALL);
}

void calculate_wall_dist(t_camera *camera, t_pos *pos, int side)
{
    double original_dist;

    if (side == 0)  // X-side hit
    {
        original_dist = (camera->map_x - pos->x + 
            (1 - camera->step_x) / 2) / camera->ray_dir_x;
    }
    else  // Y-side hit
    {
        original_dist = (camera->map_y - pos->y + 
            (1 - camera->step_y) / 2) / camera->ray_dir_y;
    }
    
    camera->perp_wall_dist = fabs(original_dist);
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
