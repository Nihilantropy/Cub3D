#include "../include/cub3D.h"

void render_floor_ceiling(t_game *game, t_render_state *state)
{
    double ray_dir_x0 = game->player.camera.dir_x - game->player.camera.plane_x;
    double ray_dir_y0 = game->player.camera.dir_y - game->player.camera.plane_y;
    double ray_dir_x1 = game->player.camera.dir_x + game->player.camera.plane_x;
    double ray_dir_y1 = game->player.camera.dir_y + game->player.camera.plane_y;

    // Get texture data for floor and ceiling
    int bits_per_pixel;
    int line_length;
    int endian;
    int *floor_data = (int *)mlx_get_data_addr(game->textures.floor,
        &bits_per_pixel, &line_length, &endian);
    int *ceiling_data = (int *)mlx_get_data_addr(game->textures.ceiling,
        &bits_per_pixel, &line_length, &endian);

    int y = game->display.height / 2; // Start at the middle of the screen
    // Draw from middle down for floor and up for ceiling
    while (y < game->display.height)
    {
        // Current y position compared to the center of the screen
        int p = y - game->display.height / 2;
        
        // Vertical position of the camera
        double pos_z = 0.5 * game->display.height;
        
        // Horizontal distance from the camera to the floor for the current row
        double row_distance = pos_z / p;
        
        // Calculate the real world step vector we have to add for each x
        double floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / game->display.width;
        double floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / game->display.width;
        
        // Real world coordinates of the leftmost column
        double floor_x = game->player.pos.x + row_distance * ray_dir_x0;
        double floor_y = game->player.pos.y + row_distance * ray_dir_y0;
        
        for(int x = 0; x < game->display.width; ++x)
        {
            // Get the texture coordinates
            int tx = (int)(TEXTURE_SIZE * (floor_x - floor(floor_x))) & (TEXTURE_SIZE - 1);
            int ty = (int)(TEXTURE_SIZE * (floor_y - floor(floor_y))) & (TEXTURE_SIZE - 1);
            
            floor_x += floor_step_x;
            floor_y += floor_step_y;
            
            // Get pixel color from floor texture
            int floor_index = ty * TEXTURE_SIZE + tx;
            int ceiling_index = ((TEXTURE_SIZE - ty - 1) * TEXTURE_SIZE + tx);
            
            // Set the ceiling (symmetrical, inverse y)
            state->img_data[(game->display.height - y - 1) * game->display.width + x] = 
                ceiling_data[ceiling_index];
            
            // Set the floor
            state->img_data[y * game->display.width + x] = 
                floor_data[floor_index];
        }
        y++;
    }
}
