#include "../include/cub3D.h"


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
