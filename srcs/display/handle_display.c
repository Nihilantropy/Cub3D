#include "../include/cub3D.h"

static void	init_cell_images(t_game *game);
static void	*create_cell_image(void *mlx_ptr, int color, int size);
static void	open_display(t_game *game);

/**
 * @brief create all images and open game window
 */
void	handle_display(t_game *game)
{
	init_cell_images(game);
	open_display(game);
	game->display.open = true;
	draw_map_2d(game);
}

static void	open_display(t_game *game)
{
	int	width;
	int	height;

	width = game->display.width;
	height = game->display.height;
	game->win_ptr = mlx_new_window(game->mlx_ptr, width, height, DISPLAY_NAME);
	if (!game->win_ptr)
		ft_exit_error(ERR_DISPLAY_OPEN);
}


/**
 * @brief create images for each cell:
 * - player -> 16 x 16 yellow
 * - wall -> 64 x 64 white
 * - floor -> 64 x 64 black
 * - unkown -> 64 x 64 grey
 */
static void	init_cell_images(t_game *game)
{
	game->minimap.images.player = create_cell_image(game->mlx_ptr, 0xFFF700, MINI_PLAYER_SIZE);
	game->minimap.images.wall = create_cell_image(game->mlx_ptr, 0xFFFFFF, MINI_CELL_SIZE);
	game->minimap.images.floor = create_cell_image(game->mlx_ptr, 0x000000, MINI_CELL_SIZE);
	game->minimap.images.unknown = create_cell_image(game->mlx_ptr, 0xAAAAAA, MINI_CELL_SIZE);
}

static void	*create_cell_image(void *mlx_ptr, int color, int size)
{
	void    *img_ptr;
	int     *img_data;
	int     bpp;
	int		size_line;
	int		endian;
	int     x;
	int		y;

	y = 0;
	img_ptr = mlx_new_image(mlx_ptr, size, size);
	img_data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			img_data[y * (size_line / 4) + x] = color;
			x++;
		}
		y++;
	}
	return (img_ptr);
}

