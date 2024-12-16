#include "../include/cub3D.h"

/**
 * @brief Draw a line between two points (x1, y1) and (x2, y2) with a specific color.
 *
 * @param mlx_ptr The mlx instance.
 * @param win_ptr The window to draw on.
 * @param x1, y1 The starting point of the line.
 * @param x2, y2 The ending point of the line.
 * @param color The color of the line.
 */
void draw_line(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr, x1, y1, color);

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