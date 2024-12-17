#include "../include/cub3D.h"

/**
 * @brief Draw a line between two points, stopping when a wall is encountered.
 *
 * @param game The game structure containing MLX pointers and map data.
 * @param x1, y1 The starting point of the line.
 * @param x2, y2 The target end point of the line.
 * @param color The color of the line.
 */
void draw_line(t_game *game, int x1, int y1, int x2, int y2, int color)
{
    // Boundary checks to prevent drawing outside window
    x1 = fmax(0, fmin(x1, WIN_WIDTH - 1));
    y1 = fmax(0, fmin(y1, WIN_HEIGHT - 1));
    x2 = fmax(0, fmin(x2, WIN_WIDTH - 1));
    y2 = fmax(0, fmin(y2, WIN_HEIGHT - 1));

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        // Check if current point is a wall in the game map
        // Assuming game->map is a 2D array of chars representing the map
        // '1' represents a wall, '0' represents an open space
        int map_x = x1 / MINI_CELL_SIZE;  // Convert screen coordinates to map coordinates
        int map_y = y1 / MINI_CELL_SIZE;

        // Stop drawing if we hit a wall
        if (map_x >= 0 && map_x < game->map.width &&
            map_y >= 0 && map_y < game->map.height &&
            game->map.matrix[map_y][map_x] == '1')
        {
            break;
        }

        // Only draw pixel if within window bounds
        if (x1 >= 0 && x1 < WIN_WIDTH && y1 >= 0 && y1 < WIN_HEIGHT)
        {
            mlx_pixel_put(game->mlx_ptr, game->win_ptr, x1, y1, color);
        }

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
}
