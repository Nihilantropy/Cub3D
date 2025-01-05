#include "../../include/cub3D_bonus.h"

static void	draw_minimap_background(t_render_state *state, t_minimap *minimap);
static void	draw_minimap_borders(t_render_state *state, t_minimap *minimap);
static void	draw_horizontal_border(t_render_state *state, t_minimap *minimap,
			int y);
static void	draw_vertical_border(t_render_state *state, t_minimap *minimap,
			int x);

/**
 * @brief Main rendering function for the minimap
 * 
 * Creates a new image for the minimap, draws all components
 * (background, walls, player, FOV), and then puts the image
 * to the window in the correct position.
 *
 * @param game Pointer to the main game structure
 */
void	render_minimap(t_game *game)
{
	t_render_state	state;
	t_minimap		*minimap;

	minimap = &game->minimap;
	state.img_ptr = mlx_new_image(game->mlx_ptr, minimap->width, 
			minimap->height);
	if (!state.img_ptr)
		return ;
	state.img_data = (int *)mlx_get_data_addr(state.img_ptr, 
			&state.bits_per_pixel, &state.line_length, &state.endian);
	if (!state.img_data)
	{
		mlx_destroy_image(game->mlx_ptr, state.img_ptr);
		return ;
	}
	draw_minimap_background(&state, minimap);
	draw_minimap_borders(&state, minimap);
	draw_minimap_walls(game, &state, minimap);
	draw_minimap_door(game, &state, minimap);
	draw_minimap_player(game, &state, minimap);
	draw_player_fov(game, &state, minimap);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, state.img_ptr,
		minimap->pos_x, minimap->pos_y);
	mlx_destroy_image(game->mlx_ptr, state.img_ptr);
}

/**
 * @brief Draws the semi-transparent background of the minimap
 *
 * @param state Pointer to the render state containing image data
 * @param minimap Pointer to minimap structure
 */
static void	draw_minimap_background(t_render_state *state, t_minimap *minimap)
{
	int	x;
	int	y;
	int	*img;

	img = state->img_data;
	y = 0;
	while (y < minimap->height)
	{
		x = 0;
		while (x < minimap->width)
		{
			img[y * (state->line_length / 4) + x] = MINIMAP_BG_COLOR;
			x++;
		}
		y++;
	}
}

/**
 * @brief Draws the border frame around the minimap
 *
 * @param state Pointer to the render state containing image data
 * @param minimap Pointer to minimap structure
 */
static void	draw_minimap_borders(t_render_state *state, t_minimap *minimap)
{
	int	i;

	i = 0;
	while (i < MINIMAP_BORDER_SIZE)
	{
		draw_horizontal_border(state, minimap, i);
		draw_horizontal_border(state, minimap, minimap->height - 1 - i);
		draw_vertical_border(state, minimap, i);
		draw_vertical_border(state, minimap, minimap->width - 1 - i);
		i++;
	}
}

/**
 * @brief Draws horizontal borders of the minimap
 *
 * @param state Pointer to the render state containing image data
 * @param minimap Pointer to minimap structure
 * @param y Y position to draw border
 */
static void	draw_horizontal_border(t_render_state *state, t_minimap *minimap,
			int y)
{
	int	x;
	int	*img;

	img = state->img_data;
	x = 0;
	while (x < minimap->width)
	{
		img[y * (state->line_length / 4) + x] = MINIMAP_BORDER_COLOR;
		x++;
	}
}

/**
 * @brief Draws vertical borders of the minimap
 *
 * @param state Pointer to the render state containing image data
 * @param minimap Pointer to minimap structure
 * @param x X position to draw border
 */
static void	draw_vertical_border(t_render_state *state, t_minimap *minimap,
			int x)
{
	int	y;
	int	*img;

	img = state->img_data;
	y = 0;
	while (y < minimap->height)
	{
		img[y * (state->line_length / 4) + x] = MINIMAP_BORDER_COLOR;
		y++;
	}
}
