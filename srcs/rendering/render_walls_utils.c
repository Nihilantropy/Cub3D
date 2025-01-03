#include "../include/cub3D.h"

/**
 * @brief Calculates dimensions for a wall slice on screen.
 * 
 * Determines height and vertical boundaries of the wall slice based on distance.
 *
 * @param slice Wall slice to calculate dimensions for.
 * @param game Game state containing display parameters.
 * @param perp_wall_dist Perpendicular distance to the wall.
 */
void calculate_wall_slice(t_wall_slice *slice, t_game *game, 
	double perp_wall_dist)
{
	slice->height = (int)(game->display.height / perp_wall_dist);
	slice->start_y = -slice->height / 2 + game->display.height / 2;
	slice->end_y = slice->height / 2 + game->display.height / 2;
	
	if (slice->start_y < 0)
		slice->start_y = 0;
	if (slice->end_y >= game->display.height)
		slice->end_y = game->display.height - 1;
}

/**
* @brief Selects appropriate wall texture based on direction and side.
* 
* Assigns texture based on ray direction and which wall side was hit.
*
* @param slice Wall slice to assign texture to.
* @param game Game state containing textures.
* @param cam Camera containing ray direction data.
*/
void select_wall_texture(t_wall_slice *slice, t_game *game, t_camera *cam)
{
	if (cam->ray_dir_y > 0 && slice->side == 1)
		slice->texture = game->textures.south;
	else if (cam->ray_dir_y <= 0 && slice->side == 1)
		slice->texture = game->textures.north;
	else if (cam->ray_dir_x > 0 && slice->side == 0)
		slice->texture = game->textures.east;
	else
		slice->texture = game->textures.west;
}

/**
* @brief Calculates texture coordinates for wall rendering.
*
* Computes wall hit point and determines texture x-coordinate based on ray direction.
*
* @param slice Wall slice to calculate texture coordinates for.
* @param game Game state containing player position.
* @param cam Camera data with ray and wall distance info.
*/
void calculate_texture_coords(t_wall_slice *slice, t_game *game, t_camera *cam)
{
	if (slice->side == 0)
		slice->wall_x = game->player.pos.y + cam->perp_wall_dist * cam->ray_dir_y;
	else
		slice->wall_x = game->player.pos.x + cam->perp_wall_dist * cam->ray_dir_x;
	slice->wall_x -= floor(slice->wall_x);
	slice->tex_x = (int)(slice->wall_x * TEXTURE_SIZE);
	if (slice->side == 0 && cam->ray_dir_x > 0)
		slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
	if (slice->side == 1 && cam->ray_dir_y < 0)
		slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
}

/**
* @brief Applies texture color to wall slice at given position.
*
* Sets color and adjusts shading for perpendicular walls.
*
* @param state Current render state.
* @param tex_data Texture data container.
* @param slice Wall slice being rendered.
* @param position Position in texture data array.
*/
void	apply_texture_color(t_render_state *state, t_render_state *tex_data,
							t_wall_slice *slice, int position)
{
	if (position >= 0 && position < TEXTURE_SIZE * TEXTURE_SIZE)
	{
		state->color = tex_data->img_data[position];
		if (slice->side == 1)
			state->color = (state->color >> 1) & 8355711;
	}
}
