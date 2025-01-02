#include "../include/cub3D.h"

void cast_ray(t_game *game, t_player *player, int x)
{
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int side;

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

void init_ray(t_camera *camera, double ray_dir_x, double ray_dir_y, t_pos *pos)
{
    // Set ray direction
    camera->ray_dir_x = ray_dir_x;
    camera->ray_dir_y = ray_dir_y;
    
    // Set initial map position
    camera->map_x = (int)pos->x;
    camera->map_y = (int)pos->y;

    // Calculate delta distances (avoid division by zero)
    camera->delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
    camera->delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
}

int perform_dda(t_game *game, t_camera *camera)
{
    bool hit = false;
    int side = -1;
    int iter = 0;

    while (hit == 0 && iter < game->map.width * game->map.height)
    {
        if (camera->side_dist_x < camera->side_dist_y)
        {
            camera->side_dist_x += camera->delta_dist_x;
            camera->map_x += camera->step_x;
            side = 0;
        }
        else
        {
            camera->side_dist_y += camera->delta_dist_y;
            camera->map_y += camera->step_y;
            side = 1;
        }

        // Check map bounds correctly
        if (camera->map_y < 0 || camera->map_y >= game->map.height ||
            camera->map_x < 0 || camera->map_x >= game->map.width)
            return (-1);
		if (game->map.matrix[camera->map_y][camera->map_x] == WALL)
			hit = true;
        iter++;
    }
    return (hit ? side : -1);
}

