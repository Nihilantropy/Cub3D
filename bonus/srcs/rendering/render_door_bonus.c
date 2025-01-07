#include "../../include/cub3D_bonus.h"

/**
* @brief Selects appropriate door texture based on door state and animation frame
*
* @param game Game structure containing door textures
* @param pos Door position
* @return void* Pointer to selected door texture
*/
void	*select_door_texture(t_game *game, t_door *door)
{
	return (game->door_system.texture[door->frame]);
}

/**
 * @brief Finds a door at the specified map position
 *
 * @param game Game structure containing door system
 * @param x Map x coordinate
 * @param y Map y coordinate
 * @return Pointer to door if found, NULL otherwise
 */
t_door	*find_door_at_position(t_game *game, int x, int y)
{
	int i;

	i = 0;
	while (i < game->door_system.door_counter)
	{
		if ((int)game->door_system.door[i].pos.x == x && 
			(int)game->door_system.door[i].pos.y == y)
			return (&game->door_system.door[i]);
		i++;
	}
	return (NULL);
}
