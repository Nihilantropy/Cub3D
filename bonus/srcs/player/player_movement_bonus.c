#include "../../include/cub3D_bonus.h"

static void	update_player_pos(t_game *game);
static void	update_direction(t_camera *cam, double rot_speed);
static void	calculate_move_step(t_player *p, double *step_x, double *step_y);

/**
 * @brief Updates player movement state based on input.
 * 
 * Sets movement flags and updates player position according to movement direction.
 * @param game Main game state containing player data.
 * @param moving Movement input flag (STILL, FORWARD, or BACKWARD).
 */
void	set_player_movement(t_game *game, int moving)
{
	game->player.moving = moving;
	if (moving == m_still)
		return ;
	update_player_pos(game);
}

/**
 * @brief Updates player's rotation angle based on rotation state.
 *
 * Modifies the player's camera direction by applying rotation speed
 * in the specified direction. No rotation occurs if state is R_STILL.
 * Updates game state to reflect changes in player orientation.
 *
 * @param game Pointer to main game structure containing player data
 * @param rotating Rotation state (R_STILL, R_LEFT, or R_RIGHT)
 */
void	set_player_rot_angle(t_game *game, int rotating)
{
	double	rot_speed;

	if (rotating == r_still)
		return ;
	if (rotating == r_left)
		rot_speed = -game->player.rot_speed;
	else
		rot_speed = game->player.rot_speed;
	update_direction(&game->player.camera, rot_speed);
	game->changed = true;
}

/**
 * @brief Updates the player's position in the game world.
 *
 * Calculates new position based on movement steps and collision detection.
 * If direct movement is blocked, attempts to slide along walls.
 * Only updates position if the new location is valid within the map bounds.
 *
 * @param game Pointer to main game structure containing player and map data
 */
static void	update_player_pos(t_game *game)
{
	double	step_x;
	double	step_y;
	t_pos	new_pos;

	new_pos = game->player.pos;
	calculate_move_step(&game->player, &step_x, &step_y);
	if (step_x == 0 && step_y == 0)
		return ;
	if (is_valid_pos((const char **)game->map.matrix, 
		game->player.pos.y + step_y, game->player.pos.x + step_x))
	{
		new_pos.x = game->player.pos.x + step_x;
		new_pos.y = game->player.pos.y + step_y;
	}
	else if (!try_slide_movement(game, &new_pos, step_x, step_y))
		return ;
	game->player.pos = new_pos;
	game->changed = true;
}

/**
* @brief Calculates movement step based on player direction.
* 
* Computes x and y movement steps using player's direction and speed.
* @param p Player data containing movement state and camera info.
* @param step_x Pointer to store calculated x step.
* @param step_y Pointer to store calculated y step.
*/
static void	calculate_move_step(t_player *player, double *step_x, double *step_y)
{
	if (player->moving == m_forward)
		move_step_forward(player, step_x, step_y);
	else if (player->moving == m_backward)
		move_step_backward(player, step_x, step_y);
	else if (player->moving == m_left)
		move_step_left(player, step_x, step_y);
	else if (player->moving == m_right)
		move_step_right(player, step_x, step_y);
	else
		move_step_still(step_x, step_y);
}

/**
 * @brief Rotates camera direction and plane vectors.
 *
 * Applies rotation matrix to update camera orientation vectors
 * using the given rotation speed.
 *
 * @param cam Pointer to camera structure
 * @param rot_speed Rotation angle in radians
 */
static void	update_direction(t_camera *cam, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cam->dir_x;
	old_plane_x = cam->plane_x;
	cam->dir_x = cam->dir_x * cos(rot_speed) - cam->dir_y * sin(rot_speed);
	cam->dir_y = old_dir_x * sin(rot_speed) + cam->dir_y * cos(rot_speed);
	cam->plane_x = cam->plane_x * cos(rot_speed) - cam->plane_y * sin(rot_speed);
	cam->plane_y = old_plane_x * sin(rot_speed) + cam->plane_y * cos(rot_speed);
}
