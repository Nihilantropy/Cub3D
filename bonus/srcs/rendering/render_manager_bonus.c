#include "../../include/cub3D_bonus.h"

/**
 * @brief Determines which texture to use based on ray hit type
 *
 * @param game Game state containing textures
 * @param cam Camera data with hit information
 * @param side Wall side that was hit
 * @return void* Pointer to the texture to be used
 */
void	*get_texture(t_game *game, t_camera *cam, int side)
{
	t_door	*door;

	door = NULL;
	if (cam->hit_type == DOOR)
	{
		door = find_door_at_position(game, cam->map_x, cam->map_y);
		return (select_door_texture(game, door));
	}
	if (cam->ray_dir_y > 0 && side == 1)
		return game->textures.south;
	else if (cam->ray_dir_y <= 0 && side == 1)
		return game->textures.north;
	else if (cam->ray_dir_x > 0 && side == 0)
		return game->textures.east;
	return game->textures.west;
}

/**
 * @brief Gets texture color including any special effects
 *
 * @param state Current render state
 * @param tex_data Texture data
 * @param slice Wall slice being rendered
 * @param position Position in texture
 */
void	get_texture_color(t_render_state *state, t_render_state *tex_data,
						t_wall_slice *slice, int position)
{
	if (position >= 0 && position < TEXTURE_SIZE * TEXTURE_SIZE)
	{
		state->color = tex_data->img_data[position];
		if (slice->side == 1)
			state->color = (state->color >> 1) & 8355711;
	}
}
