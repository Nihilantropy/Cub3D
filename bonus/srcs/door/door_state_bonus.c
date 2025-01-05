#include "../../include/cub3D_bonus.h"

bool	player_on_door_pos(t_player *player, t_door *door)
{
	if ((int)player->pos.y == (int)door->pos.y
		&& (int)player->pos.x == (int)door->pos.x)
		return (true);
	return (false);
}
