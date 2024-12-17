#include "../include/cub3D.h"

/**
 * @brief Draws a ray from the player's position to the wall hit coordinates.
 */
void draw_ray(t_game *game, t_player *player)
{
    int x1 = (int)player->pos.x_screen; // Ensure integer coordinates
    int y1 = (int)player->pos.y_screen;
    int x2 = (int)player->camera.wall_hit_x;
    int y2 = (int)player->camera.wall_hit_y;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;  // Determine step direction for x
    int sy = (y1 < y2) ? 1 : -1;  // Determine step direction for y
    int err = dx - dy;

    // Initialize side_dist_x and side_dist_y
    float side_dist_x = 0;
    float side_dist_y = 0;

    // Initialize delta values (distance to the next grid)
    float delta_dist_x = (dx == 0) ? 1e30 : (float)dx; // Avoid division by zero for vertical rays
    float delta_dist_y = (dy == 0) ? 1e30 : (float)dy; // Avoid division by zero for horizontal rays

    // If the ray is moving in the x direction
    if (sx > 0)
        side_dist_x = (x1 - (int)x1) * delta_dist_x;
    else
        side_dist_x = ((int)x1 + 1 - x1) * delta_dist_x;

    // If the ray is moving in the y direction
    if (sy > 0)
        side_dist_y = (y1 - (int)y1) * delta_dist_y;
    else
        side_dist_y = ((int)y1 + 1 - y1) * delta_dist_y;

    printf("Ray start: x1 = %d, y1 = %d, dx = %d, dy = %d\n", x1, y1, dx, dy);
    printf("Initial side_dist_x = %.2f, side_dist_y = %.2f\n", side_dist_x, side_dist_y);

    while (1)
    {
        // Print current step for debugging
        printf("Ray step: map_x = %d, map_y = %d, side_dist_x = %.2f, side_dist_y = %.2f\n",
               x1, y1, side_dist_x, side_dist_y);

        mlx_pixel_put(game->mlx_ptr, game->win_ptr, x1, y1, GREEN);  // Debugging color

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }

    printf("Ray finished at x = %d, y = %d\n", x1, y1);
}