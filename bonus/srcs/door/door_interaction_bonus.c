#include "../../include/cub3D_bonus.h"

static t_door	*find_closest_door(t_game *game);
static void		toggle_door_state(t_door *door);
static bool		is_within_door_range(t_game *game, t_door *door);

/**
* @brief Handles door interaction when player presses space
*
* @param game Game structure containing door system
*/
void	handle_door_interaction(t_game *game)
{
	t_door	*closest_door;

	closest_door = find_closest_door(game);
	if (!closest_door || !is_within_door_range(game, closest_door))
		return ;
	if (closest_door->active || player_on_door_pos(&game->player, closest_door))
		return ;
	toggle_door_state(closest_door);
	if (closest_door->state == door_closing)
		update_map_matrix(game, (int)closest_door->pos.y, (int)closest_door->pos.x, false);
	closest_door->active = true;
	game->changed = true;
}

/**
* @brief Toggles door state when player interacts with it
*
* @param door Door to interact with
*/
static void	toggle_door_state(t_door *door)
{
	door->anim_counter = 0;
	if (door->state == door_closed)
		door->state = door_opening;
	else if (door->state == door_open)
		door->state = door_closing;
}

/**
* @brief Finds closest door that player can interact with
*
* @param game Game structure containing door system
* @return t_door* Pointer to closest door or NULL if none in range
*/
static t_door	*find_closest_door(t_game *game)
{
	t_door	*closest_door = NULL;
	double	min_distance = DOOR_INTERACT_DIST;
	int		i;
	
	i = 0;
	while (i < game->door_system.door_counter)
	{
		double dx = game->player.pos.x - game->door_system.door[i].pos.x;
		double dy = game->player.pos.y - game->door_system.door[i].pos.y;
		double distance = sqrt(dx * dx + dy * dy);
		if (distance < min_distance)
		{
			min_distance = distance;
			closest_door = &game->door_system.door[i];
		}
		i++;
	}
	return (closest_door);
}

/**
* @brief Checks if player is close enough to interact with a door
*
* @param game Game structure containing player and door data
* @param door Door to check distance to
* @return bool true if within interaction distance, false otherwise
*/
static bool	is_within_door_range(t_game *game, t_door *door)
{
	double dx = game->player.pos.x - door->pos.x;
	double dy = game->player.pos.y - door->pos.y;
	double distance = sqrt(dx * dx + dy * dy);
	return (distance <= DOOR_INTERACT_DIST);
}

void	update_map_matrix(t_game *game, int y, int x, bool open)
{
	if (open)
		game->map.matrix[y][x] = FLOOR;
	else
		game->map.matrix[y][x] = DOOR;
}
