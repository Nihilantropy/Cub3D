#include "../include/cub3D.h"

/**
 * @brief Draw a line using Bresenham's line algorithm
 * This function draws a line between two points using an optimized 
 * integer-based algorithm. It handles all octants correctly and
 * draws pixel by pixel for smooth line rendering.
 * 
 * @param game Game state containing MLX info
 * @param x1 Starting X coordinate
 * @param y1 Starting Y coordinate 
 * @param x2 Ending X coordinate
 * @param y2 Ending Y coordinate
 * @param color Color of the line in RGB format
 */
void	draw_line(t_game *game, int x1, int y1, int x2, int y2, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = (dx > dy ? dx : -dy) / 2;

	while (1)
	{
		if (x1 >= 0 && y1 >= 0 && x1 < game->display.width
			&& y1 < game->display.height)
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y1 += sy;
		}
	}
}