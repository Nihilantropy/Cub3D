#include "../../include/cub3D_bonus.h"

static int	get_texture_pixel(t_render_state *tex_data, t_wall_slice *slice,
							double tex_pos, int x);
static bool	is_transparent_pixel(unsigned int color);

/**
* @brief Renders a wall slice with transparency
*
* @param state Current render state
* @param slice Wall slice definition
* @param game Game state information
* @param x Current x position on screen
*/
void	render_transparent_slice(t_render_state *state, t_wall_slice *slice,
								t_game *game, int x)
{
	int				y;
	double			step;
	double			tex_pos;
	t_render_state	tex_data;
	unsigned int				color;

	if (!init_texture_rendering(slice, &tex_data, &step))
		return ;
	tex_pos = (slice->start_y - game->display.height / 2 + 
			slice->height / 2) * step;
	y = slice->start_y;
	while (y < slice->end_y)
	{
		color = get_texture_pixel(&tex_data, slice, tex_pos, x);
		if (!is_transparent_pixel(color))
		{
			if (y >= 0 && y < game->display.height)
				state->img_data[y * game->display.width + x] = color;
		}
		tex_pos += step;
		y++;
	}
}

/**
* @brief Gets a pixel color from the texture
*
* @param tex_data Texture data
* @param slice Wall slice information
* @param tex_pos Current texture position
* @param x Current x position
* @return int Color value at the specified position
*/
static int	get_texture_pixel(t_render_state *tex_data, t_wall_slice *slice,
							double tex_pos, int x)
{
	int	tex_y;
	int	position;
	(void)x;

	tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
	position = TEXTURE_SIZE * tex_y + slice->tex_x;
	if (position >= 0 && position < TEXTURE_SIZE * TEXTURE_SIZE)
		return (tex_data->img_data[position]);
	return (0);
}

/**
* @brief Checks if a pixel in the texture should be transparent
*
* @param color Color value to check
* @return true if pixel should be transparent, false otherwise
*/
static bool	is_transparent_pixel(unsigned int color)
{
	return (color == 0 || color == TRANSPARENT);
}
