#ifndef PLAYER_H
# define PLAYER_H

# include <stdbool.h>

/* Movement and rotation constants */
# define M_FORWARD 1
# define M_BACKWARD -1
# define M_STILL 0
# define R_LEFT -1
# define R_RIGHT 1
# define R_STILL 0
# define P_SPEED 0.1
# define R_SPEED 0.1

/* Field of view and projection constants */
# define FOV_ANGLE (60.0 * M_PI / 180.0)
# define PLAYER_RADIUS 0.2

/* Minimap related */
# define MINI_PLAYER_SIZE 16
# define MINI_PLAYER_TEXTURE "texture/debug/minimap_player.xpm"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/**
 * @brief Camera structure containing all raycasting-related data.
 * Consolidates viewing frustum and ray calculations including
 * direction vectors, ray properties, and DDA algorithm variables.
 */
typedef struct s_camera
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	perp_wall_dist;
	int		side;
}	t_camera;

/**
 * @brief Position structure handling both world and screen coordinates
 */
typedef struct s_pos
{
	double	x;
	double	y;
	int		x_screen;
	int		y_screen;
}	t_pos;

/**
 * @brief Movement state structure tracking all possible movement directions
 */
typedef struct s_moving
{
	bool	forward;
	bool	backward;
}	t_moving;

/**
 * @brief Player structure containing all player-related data including
 * position, movement state, camera information and speeds
 */
typedef struct s_player
{
	t_pos		pos;
	t_moving	moving;
	t_camera	camera;
	double		speed;
	double		rot_speed;
	char		face;
}	t_player;

#endif