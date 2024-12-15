#include "../include/cub3D.h"

static void	update_player_pos(t_game *game);
static void	update_player_angle(t_game *game);
static bool is_valid_pos(const char **matrix, double new_y, double new_x);

/**
 * @brief based on the moving input, set the correct
 *	moving boolean var and update player position.
 * 
 * @param moving incoming moving input
 */
void	set_player_movement(t_game *game, int moving)
{
	if (moving == M_STILL)
	{
		game->player.moving.forward = false;
		game->player.moving.backward = false;
		return;
	}
	game->player.moving.forward = (moving == M_FORWARD);
	game->player.moving.backward = (moving == M_BACKWARD);
	update_player_pos(game);
}

/**
 * @brief based on the rotating input, set the correct
 *	boolean var and update player rotation angle.
 * 
 * @param rotating incoming rotation input
 */
void	set_player_rot_angle(t_game *game, int rotating)
{
	if (rotating == R_STILL)
	{
		game->player.rot.left = false;
		game->player.rot.right = false;
		return;
	}
	game->player.rot.left = (rotating == R_LEFT);
	game->player.rot.right = (rotating == R_RIGHT);
	update_player_angle(game);
}

/**
 * @brief update the player position on the map
 * using the current rotation angle.
 * 
 * Check if the new position is valid before update.
 */
static void	update_player_pos(t_game *game)
{
	double	new_x;
	double	new_y;
	double	angle;

	new_x = game->player.pos.x;
	new_y = game->player.pos.y;
	angle = game->player.rot.current_angle;
	if (game->player.moving.forward)
	{
		new_x += game->player.speed * cos(angle);
		new_y += game->player.speed * sin(angle);
	}
	else if (game->player.moving.backward)
	{
		new_x -= game->player.speed * cos(angle);
		new_y -= game->player.speed * sin(angle);
	}
	if (is_valid_pos(game->map.matrix, new_y, new_x))
	{
		game->player.pos.x = new_x;
		game->player.pos.y = new_y;
		game->minimap.changed = true;
	}
	printf("Checking position (%.2f, %.2f): Grid (%d, %d) - Valid: %s\n",
       new_x, new_y, (int)new_x, (int)new_y,
       is_valid_pos(game->map.matrix, new_y, new_x) ? "YES" : "NO");
}

/**
 * @brief update player rot based on the player rotation speed
 * ensuring to stay between 0 and 360 degree
 */
static void	update_player_angle(t_game *game)
{
	if (game->player.rot.left)
	{
		game->player.rot.current_angle -= game->player.rot_speed;
		if (game->player.rot.current_angle < 0)
			game->player.rot.current_angle += 2 * M_PI;
	}
	else if (game->player.rot.right)
	{
		game->player.rot.current_angle += game->player.rot_speed;
		if (game->player.rot.current_angle >= 2 * M_PI)
			game->player.rot.current_angle -= 2 * M_PI;
	}
	game->minimap.changed = true;
	printf("Current Angle: %.2f radians\n", game->player.rot.current_angle);
}

/**
 * @brief check if the next position is valid
 * returns corrisponding boolean based on condition matching
 */
static bool is_valid_pos(const char **matrix, double new_y, double new_x)
{
    int grid_x;
    int grid_y;
	
	grid_x = (int)new_x;
	grid_y = (int)new_y;

	return (
		grid_y >= 0 && matrix[grid_y] != NULL &&
		grid_x >= 0 && matrix[grid_y][grid_x] != '\0' &&
		(matrix[grid_y][grid_x] == FLOOR ||
		is_player_char(matrix[grid_y][grid_x]))
	);
}
