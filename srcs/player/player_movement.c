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
static void update_player_pos(t_game *game)
{
    double new_x;
    double new_y;
    t_player *p;
    double move_step_x;
    double move_step_y;

    new_x = game->player.pos.x;
    new_y = game->player.pos.y;
    p = &game->player;

    // Calculate full movement steps
    if (p->moving.forward)
    {
        move_step_x = p->camera.dir_x * p->speed;
        move_step_y = p->camera.dir_y * p->speed;
    }
    else if (p->moving.backward)
    {
        move_step_x = -p->camera.dir_x * p->speed;
        move_step_y = -p->camera.dir_y * p->speed;
    }
    else
        return;

    // Try full movement first
    if (is_valid_pos((const char **)game->map.matrix, 
        p->pos.y + move_step_y, p->pos.x + move_step_x))
    {
        new_x = p->pos.x + move_step_x;
        new_y = p->pos.y + move_step_y;
    }
    else
    {
        // Try sliding along X axis
        if (is_valid_pos((const char **)game->map.matrix, 
            p->pos.y, p->pos.x + move_step_x))
        {
            new_x = p->pos.x + move_step_x;
            // Try partial Y movement
            double partial_y = move_step_y * 0.5;
            if (is_valid_pos((const char **)game->map.matrix, 
                p->pos.y + partial_y, new_x))
                new_y = p->pos.y + partial_y;
        }

        // Try sliding along Y axis
        if (is_valid_pos((const char **)game->map.matrix, 
            p->pos.y + move_step_y, p->pos.x))
        {
            new_y = p->pos.y + move_step_y;
            // Try partial X movement
            double partial_x = move_step_x * 0.5;
            if (is_valid_pos((const char **)game->map.matrix, 
                new_y, p->pos.x + partial_x))
                new_x = p->pos.x + partial_x;
        }
    }

    // Update position if any movement was valid
    if (new_x != p->pos.x || new_y != p->pos.y)
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
    // Check the corners of the player's hitbox
    double check_points[][2] = {
        {new_x - PLAYER_RADIUS, new_y - PLAYER_RADIUS},  // Top-left
        {new_x + PLAYER_RADIUS, new_y - PLAYER_RADIUS},  // Top-right
        {new_x - PLAYER_RADIUS, new_y + PLAYER_RADIUS},  // Bottom-left
        {new_x + PLAYER_RADIUS, new_y + PLAYER_RADIUS}   // Bottom-right
    };

    // Check each corner
    for (int i = 0; i < 4; i++)
    {
        int grid_x = (int)check_points[i][0];
        int grid_y = (int)check_points[i][1];

        // Basic boundary check
        if (grid_y < 0 || matrix[grid_y] == NULL ||
            grid_x < 0 || matrix[grid_y][grid_x] == '\0')
            return (false);

        // Check if any corner would be inside a wall
        if (matrix[grid_y][grid_x] != FLOOR &&
            !is_player_char(matrix[grid_y][grid_x]))
            return (false);
    }

    // Additional check for very close proximity to walls
    const double WALL_BUFFER = 0.1;  // Extra buffer distance from walls
    double check_radius = PLAYER_RADIUS + WALL_BUFFER;
    
    // Check more points around the circle for smoother collision
    for (int angle = 0; angle < 360; angle += 45)  // Check every 45 degrees
    {
        double check_x = new_x + check_radius * cos(angle * M_PI / 180.0);
        double check_y = new_y + check_radius * sin(angle * M_PI / 180.0);
        
        int grid_x = (int)check_x;
        int grid_y = (int)check_y;

        if (grid_y < 0 || matrix[grid_y] == NULL ||
            grid_x < 0 || matrix[grid_y][grid_x] == '\0' ||
            matrix[grid_y][grid_x] != FLOOR)
            return (false);
    }

    return (true);
}
