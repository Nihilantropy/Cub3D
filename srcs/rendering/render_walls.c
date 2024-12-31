#include "../include/cub3D.h"

// static void calculate_wall_slice(t_wall_slice *slice, t_game *game, 
//     double perp_wall_dist)
// {
//     slice->height = (int)(game->display.height / perp_wall_dist);
//     slice->start_y = -slice->height / 2 + game->display.height / 2;
//     slice->end_y = slice->height / 2 + game->display.height / 2;
    
//     if (slice->start_y < 0)
//         slice->start_y = 0;
//     if (slice->end_y >= game->display.height)
//         slice->end_y = game->display.height - 1;
// }

// static void draw_textured_wall_slice(t_render_state *state, t_wall_slice *slice, 
//     t_game *game, int x)
// {
//     // printf("Drawing wall slice: x=%d, height=%d, start_y=%d, end_y=%d\n", 
//     //        x, slice->height, slice->start_y, slice->end_y); // Debug print

//     int y;
//     double step;
//     double tex_pos;
//     int tex_y;
//     int color;
//     int *texture_data;
//     int bits_per_pixel;
//     int line_length;
//     int endian;

//     if (!slice->texture)
//     {
//         printf("Error: Null texture for wall slice\n");
//         return;
//     }

//     texture_data = (int *)mlx_get_data_addr(slice->texture, &bits_per_pixel,
//         &line_length, &endian);

//     if (!texture_data)
//     {
//         printf("Error: Failed to get texture data\n");
//         return;
//     }

//     // Calculate step size for texture
//     step = 1.0 * TEXTURE_SIZE / slice->height;
//     tex_pos = (slice->start_y - game->display.height / 2 + slice->height / 2) * step;

//     // Draw the wall slice
//     y = slice->start_y;
//     while (y < slice->end_y)
//     {
//         tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
//         tex_pos += step;

//         // Get pixel color from texture
//         color = texture_data[TEXTURE_SIZE * tex_y + slice->tex_x];
        
//         // Apply shading for sides
//         if (slice->side == 1)
//             color = (color >> 1) & 8355711;

//         // Store pixel in frame buffer
//         if (y * game->display.width + x >= 0 && 
//             y * game->display.width + x < game->display.width * game->display.height)
//         {
//             state->img_data[y * game->display.width + x] = color;
//         }
//         y++;
//     }
// }



// static void calculate_texture_coords(t_wall_slice *slice, t_game *game, t_camera *cam)
// {
//     // Calculate wall X coordinate (where exactly the wall was hit)
//     if (slice->side == 0)
//         slice->wall_x = game->player.pos.y + cam->perp_wall_dist * cam->ray_dir_y;
//     else
//         slice->wall_x = game->player.pos.x + cam->perp_wall_dist * cam->ray_dir_x;
//     slice->wall_x -= floor(slice->wall_x);

//     // Calculate texture X coordinate
//     slice->tex_x = (int)(slice->wall_x * TEXTURE_SIZE);
//     if (slice->side == 0 && cam->ray_dir_x > 0)
//         slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
//     if (slice->side == 1 && cam->ray_dir_y < 0)
//         slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
// }

void render_walls(t_game *game, t_render_state *state)
{
    int x;
    
    printf("DEBUG: Render walls called with map size: width=%d, height=%d\n",
        game->map.width, game->map.height);
    
    x = 0;
    while (x < game->display.width)
    {
        // Cast ray for this vertical strip
        cast_ray(game, &game->player, x, state);
        x++;
    }
}