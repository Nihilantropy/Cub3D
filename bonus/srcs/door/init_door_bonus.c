#include "../../include/cub3D_bonus.h"

void	init_doors(t_game *game)
{
	int	i;

	game->door_system.door = malloc(sizeof(t_door) * game->door_system.door_counter);
	if (!game->door_system.door)
		ft_exit_error(ERR_ALLOC_DOOR);
	i = 0;
	while (i < game->door_system.door_counter)
	{
		game->door_system.door[i].pos.x = 0;
		game->door_system.door[i].pos.y = 0;
		game->door_system.door[i].frame = 0;
		game->door_system.door[i].anim_counter = 0;
		game->door_system.door[i].state = door_closed;
		game->door_system.door[i].active = false;
		game->door_system.door[i].id = i + 1;
		game->door_system.door[i].perp_dist = 0.0;
		game->door_system.door[i].side = -1;
		game->door_system.door[i].is_rendering = false;
		i++;
	}
}
