// #include "../include/cub3D.h"

// /**
//  * @brief Draw a single ray from player position until wall collision
//  * Visualizes the exact path and collision detection of raycasting
//  * by drawing line segments that represent ray movement
//  * 
//  * @param game Main game structure containing map and display data
//  * @param ray_angle The current angle of ray being cast
//  * @param max_distance Maximum ray travel distance before stopping
//  * @param ray_color Color used to draw the ray path
//  * 
//  * @return true if ray hits wall, false if reaches max distance
//  */
// bool draw_debug_ray(t_game *game, double ray_angle, double max_distance, int ray_color)
// {
//     double ray_x = game->player.pos.x;
//     double ray_y = game->player.pos.y;
//     double ray_cos = cos(ray_angle) * 0.1;
//     double ray_sin = sin(ray_angle) * 0.1;
//     double distance = 0;
//     int screen_x = (int)(ray_x * MINI_CELL_SIZE);
//     int screen_y = (int)(ray_y * MINI_CELL_SIZE);

//     while (distance < max_distance)
//     {
//         int map_x = (int)ray_x;
//         int map_y = (int)ray_y;

//         if (map_y >= 0 && map_x >= 0 && 
//             game->map.matrix[map_y] != NULL && 
//             game->map.matrix[map_y][map_x] == WALL)
//             return true;

//         int new_screen_x = (int)(ray_x * MINI_CELL_SIZE);
//         int new_screen_y = (int)(ray_y * MINI_CELL_SIZE);
        
//         draw_line(game, screen_x, screen_y, new_screen_x, new_screen_y, ray_color);
        
//         screen_x = new_screen_x;
//         screen_y = new_screen_y;
//         ray_x += ray_cos;
//         ray_y += ray_sin;
//         distance += 0.1;
//     }
//     return false;
// }

// /**
//  * @brief Visualize player's complete field of view
//  * Creates a visual cone showing all rays within FOV angle
//  * Draws multiple rays between left and right view bounds
//  * Uses different colors to distinguish central ray
//  * 
//  * @param game Main game structure with player and view data
//  */
// void draw_player_fov(t_game *game)
// {
//     double fov_half = game->player.camera.fov * (M_PI / 180.0) / 2;
//     double start_angle = game->player.rot.current_angle - fov_half;
//     double end_angle = game->player.rot.current_angle + fov_half;
//     int num_rays = 50;
//     double angle_step = (end_angle - start_angle) / num_rays;
//     double current_angle = start_angle;

//     for (int i = 0; i < num_rays; i++)
//     {
//         int ray_color = (i == num_rays / 2) ? RED : 0xFFFF00;
//         draw_debug_ray(game, current_angle, 20.0, ray_color);
//         current_angle += angle_step;
//     }
// }

// /**
//  * @brief Main entry point for ray visualization system
//  * Handles drawing of both direction indicator and FOV
//  * Shows the complete raycasting visualization from top-down view
//  * Integrates with the game's main rendering pipeline
//  * 
//  * @param game Main game structure
//  * @param player Player data structure
//  */
// void draw_ray(t_game *game, t_player *player)
// {
//     int dir_x = player->pos.x_screen + cos(player->rot.current_angle) * MINI_CELL_SIZE;
//     int dir_y = player->pos.y_screen + sin(player->rot.current_angle) * MINI_CELL_SIZE;
    
//     draw_line(game, player->pos.x_screen, player->pos.y_screen, dir_x, dir_y, RED);
//     draw_player_fov(game);
// }
