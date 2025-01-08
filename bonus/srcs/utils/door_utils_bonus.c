#include "../../include/cub3D_bonus.h"

/**
* @brief Frees all allocated door textures and door array
*
* @param game The game structure containing door system data
*/
void	free_door_system(t_game *game)
{
	int i;

	if (game->door_system.door)
		free(game->door_system.door);
	if (game->mlx_ptr)
	{
		i = 0;
		while (i < FRAME_RATE)
		{
			if (game->door_system.texture[i])
				mlx_destroy_image(game->mlx_ptr, game->door_system.texture[i]);
			i++;
		}
	}
}
