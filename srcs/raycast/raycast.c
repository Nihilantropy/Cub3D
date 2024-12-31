#include "../include/cub3D.h"

void cast_ray(t_game *game, t_player *player, int x, t_render_state *state)
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
        
        // Calculate wall height and draw it
        int wall_height = calculate_wall_height(game, player->camera.perp_wall_dist);
        draw_wall_stripe(game, x, wall_height, state);
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

    // printf("Ray init: dir=(%.2f,%.2f), pos=(%.2f,%.2f), map=(%d,%d), delta=(%.2f,%.2f)\n",
    //        ray_dir_x, ray_dir_y, pos->x, pos->y, 
    //        camera->map_x, camera->map_y,
    //        camera->delta_dist_x, camera->delta_dist_y);
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

int perform_dda(t_game *game, t_camera *camera)
{
    int hit = 0;
    int side = -1;
    int iter = 0;
    
    printf("\nDDA Start: pos=(%d,%d), actual_map_size=(%d,%d)\n", 
        camera->map_x, camera->map_y, game->map.width, game->map.height);
    
    // Print current cell before starting DDA
    printf("Starting cell content: %c\n", 
        game->map.matrix[camera->map_y][camera->map_x]);

    while (hit == 0 && iter < game->map.width * game->map.height)
    {
        // Store previous position for debugging
        int prev_x = camera->map_x;
        int prev_y = camera->map_y;

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

        // Print step information
        printf("Step from (%d,%d) to (%d,%d)\n", 
            prev_x, prev_y, camera->map_x, camera->map_y);

        // Check map bounds correctly
        if (camera->map_y < 0 || camera->map_y >= game->map.height ||
            camera->map_x < 0 || camera->map_x >= game->map.width)
        {
            printf("DDA: Out of bounds at (%d,%d), map size is (%d,%d)\n",
                camera->map_x, camera->map_y, game->map.width, game->map.height);
            return (-1);
        }

        // Check current cell
        char current_cell = game->map.matrix[camera->map_y][camera->map_x];
        printf("Checking cell (%d,%d): content=%c\n", 
            camera->map_x, camera->map_y, current_cell);

        hit = (current_cell == WALL);
        if (hit)
            printf("DDA: Wall hit at (%d,%d)\n", camera->map_x, camera->map_y);
        
        iter++;
    }

    return (hit ? side : -1);
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

    printf("Wall distance calculation:\n");
    printf("  Player pos: (%.2f, %.2f)\n", pos->x, pos->y);
    printf("  Wall hit: (%d, %d)\n", camera->map_x, camera->map_y);
    printf("  Ray dir: (%.2f, %.2f)\n", camera->ray_dir_x, camera->ray_dir_y);
    printf("  Side hit: %s\n", side == 0 ? "X-side" : "Y-side");
    printf("  Distance: %.2f\n", camera->perp_wall_dist);
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

void draw_wall_stripe(t_game *game, int x, int wall_height, t_render_state *state)
{
    int draw_start;
    int draw_end;
    int y;
    int color;

    // Calculate vertical strip position
    draw_start = -wall_height / 2 + game->display.height / 2;
    if (draw_start < 0) 
        draw_start = 0;
        
    draw_end = wall_height / 2 + game->display.height / 2;
    if (draw_end >= game->display.height)
        draw_end = game->display.height - 1;

    // Use simple color for testing (we'll add textures later)
    color = RED;
    
    // Draw vertical strip
    y = draw_start;
    while (y <= draw_end)
    {
        int index = y * game->display.width + x;
        if (index >= 0 && index < game->display.width * game->display.height)
            state->img_data[index] = color;
        y++;
    }
}