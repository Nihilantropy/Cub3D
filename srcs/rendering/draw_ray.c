#include "../include/cub3D.h"

/**
 * @brief Draws a ray from the player's position to the wall hit coordinates.
 *
 * @param game Pointer to the game structure containing the MLX instance.
 * @param player Pointer to the player structure containing the position and wall hit coordinates.
 */
void draw_ray(t_game *game, t_player *player)
{
    int x0 = (int)(player->pos.x * MINI_CELL_SIZE);
    int y0 = (int)(player->pos.y * MINI_CELL_SIZE);
    int x1 = (int)(player->camera.wall_hit_x * MINI_CELL_SIZE);
    int y1 = (int)(player->camera.wall_hit_y * MINI_CELL_SIZE);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        mlx_pixel_put(game->mlx_ptr, game->win_ptr, x0, y0, 0xFFFFFF); // Draw the pixel in white
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
