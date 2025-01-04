#include "../../include/cub3D_bonus.h"

static void render_textured_wall_slice(t_render_state *state, t_wall_slice *slice, 
									t_game *game, int x);
static bool	init_texture_rendering(t_wall_slice *slice, t_render_state *tex_data, 
								double *step);
static bool get_texture_data(t_wall_slice *slice, t_render_state *tex_data);

void render_walls(t_game *game, t_render_state *state, int x)
{
	t_wall_slice slice;
	
	cast_ray(game, &game->player, x);
	calculate_wall_slice(&slice, game, game->player.camera.perp_wall_dist);
	slice.side = game->player.camera.side;
	slice.distance = game->player.camera.perp_wall_dist;
	calculate_texture_coords(&slice, game, &game->player.camera);
	select_wall_texture(&slice, game, &game->player.camera);
	render_textured_wall_slice(state, &slice, game, x);
}

/**
* @brief Renders a textured wall slice to the screen.
* 
* This function applies the texture to a wall slice and renders it onto the display
* based on the calculated texture position.
*
* @param state The render state that holds the image data to be modified.
* @param slice The wall slice to be rendered.
* @param game The game state to access display parameters.
* @param x The x-coordinate of the current slice on the screen.
* @return None.
*/
static void	render_textured_wall_slice(t_render_state *state, t_wall_slice *slice,
									t_game *game, int x)
{
	int				y;
	double			step;
	double			tex_pos;
	t_render_state	tex_data;

	if (!init_texture_rendering(slice, &tex_data, &step))
		return ;
	tex_pos = (slice->start_y - game->display.height / 2 + 
			slice->height / 2) * step;
	y = slice->start_y;
	while (y < slice->end_y)
	{
		apply_texture_color(state, &tex_data, slice, 
						TEXTURE_SIZE * ((int)tex_pos & (TEXTURE_SIZE - 1)) + 
						slice->tex_x);
		if (y * game->display.width + x >= 0 && 
			y * game->display.width + x < game->display.width * 
			game->display.height)
			state->img_data[y * game->display.width + x] = state->color;
		tex_pos += step;
		y++;
	}
}

/**
* @brief Initializes rendering parameters for wall textures.
* 
* Gets texture data and calculates texture mapping step size.
*
* @param slice The wall slice containing texture information.
* @param tex_data Structure to store the texture rendering data.
* @param step Calculated step size for texture mapping.
* @return True if initialization succeeds, false otherwise.
*/
static bool	init_texture_rendering(t_wall_slice *slice, t_render_state *tex_data, 
								double *step)
{
	if (!get_texture_data(slice, tex_data))
		return (false);
	*step = 1.0 * TEXTURE_SIZE / slice->height;
	return (true);
}

/**
* @brief Retrieves texture data for a wall slice.
* 
* This function extracts the texture data for the given wall slice and handles errors if the texture
* is null or retrieval fails.
*
* @param slice The wall slice containing the texture information.
* @param tex_data A pointer to a t_render_state structure to store the texture data.
* @return True if the texture data was successfully retrieved, otherwise false.
*/
static bool get_texture_data(t_wall_slice *slice, t_render_state *tex_data)
{
	if (!slice->texture)
	{
		printf("Error: Null texture for wall slice\n");
		return (false);
	}

	tex_data->img_data = (int *)mlx_get_data_addr(slice->texture, &tex_data->bits_per_pixel,
												&tex_data->line_length, &tex_data->endian);
	if (!tex_data->img_data)
	{
		printf("Error: Failed to get texture data\n");
		return (false);
	}

	return (true);
}
