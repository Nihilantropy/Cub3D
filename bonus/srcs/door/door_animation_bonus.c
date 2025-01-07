#include "../../include/cub3D_bonus.h"

static void	set_door_open(t_game *game, t_door *door);
static void	set_door_close(t_door *door);

/**
* @brief Updates door state and animation frame
*
* @param door Door structure to update
*/
void	update_door_animation(t_game *game, t_door *door)
{
	if (!door->active)
		return;
	door->anim_counter++;
	if (door->anim_counter >= DOOR_ANIM_SPEED)
	{
		door->anim_counter = 0;
		if (door->anim_state == door_opening)
		{
			if (door->frame < DOOR_FRAMES - 1)
				door->frame++;
			else
				set_door_open(game, door);
		}
		else if (door->anim_state == door_closing)
		{
			if (door->frame > 0)
				door->frame--;
			else
				set_door_close(door);
		}
	}
}

static void	set_door_open(t_game *game, t_door *door)
{
	door->anim_state = door_open;
	update_map_matrix(game, (int)door->pos.y, (int)door->pos.x, true);
	door->active = false;
}

static void	set_door_close(t_door *door)
{
	door->anim_state = door_closed;
	door->active = false;
}
