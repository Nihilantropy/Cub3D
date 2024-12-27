#include "../include/cub3D.h"

static void	update_player_pos(t_game *game);
static void	update_direction(t_camera *cam, double rot_speed);
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
	double	rot_speed;

	if (rotating == R_STILL)
		return;
	if (rotating == R_LEFT)
		rot_speed = -game->player.rot_speed;
	else
		rot_speed = game->player.rot_speed;
	update_direction(&game->player.camera, rot_speed);
	game->minimap.changed = true;
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
	t_player *p;

	new_x = game->player.pos.x;
	new_y = game->player.pos.y;
	p = &game->player;
	if (p->moving.forward)
	{
		new_x += p->camera.dir_x * p->speed;
		new_y += p->camera.dir_y * p->speed;
	}
	else if (p->moving.backward)
	{
		new_x -= p->camera.dir_x * p->speed;
		new_y -= p->camera.dir_y * p->speed;
	}
	if (is_valid_pos((const char **)game->map.matrix, new_y, new_x))
	{
		p->pos.x = new_x;
		p->pos.y = new_y;
		game->minimap.changed = true;
	}
}

/**
 * @brief update camera direction and plane vectors based on rotation speed.
 * Uses rotation matrix to update both the direction vector and camera plane.
 * 
 * @param cam camera info containing direction and plane vectors
 * @param rot_speed rotation speed in radians
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
