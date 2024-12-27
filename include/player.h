#ifndef PLAYER_H
# define PLAYER_H

# include <stdbool.h>

# define M_FORWARD 1
# define M_BACKWARD -1
# define M_STILL 0
# define R_LEFT -1
# define R_RIGHT 1
# define R_STILL 0
# define P_SPEED 0.1
# define R_SPEED 0.1
# define P_FOV 135.0

# define MINI_PLAYER_TEXTURE "texture/debug/minimap_player.xpm"

#ifndef M_PI
# define M_PI 3.14
#endif

#ifndef M_PI_2
# define M_PI_2 1.57
#endif

/**
 * @brief Stores raycasting information.
 *
 * @var fov The field of view in degrees (e.g., 135°).
 * @var ray_dir_x X component of the current ray's direction vector.
 * @var ray_dir_y Y component of the current ray's direction vector.
 * @var map_x Current X index of the map grid being checked.
 * @var map_y Current Y index of the map grid being checked.
 * @var side_dist_x Distance to the first X-side of the grid being hit.
 * @var side_dist_y Distance to the first Y-side of the grid being hit.
 * @var delta_dist_x Distance between vertical grid lines the ray intersects.
 * @var delta_dist_y Distance between horizontal grid lines the ray intersects.
 * @var perp_wall_dist Perpendicular distance from the player to the wall.
 * @var start_x Starting X position for accurate distance calculation
 * @var start_y Starting Y position for accurate distance calculation
 */
typedef struct s_camera
{
    double  fov;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  wall_hit_x;
    double  wall_hit_y;
    double  perp_wall_dist;
    double  start_x;
    double  start_y;
}   t_camera;


/**
 * @brief Stores moving infos.
 */
typedef struct s_moving
{
	bool	forward;
	bool	backward;
}	t_moving;


/**
 * @brief Stores the player's position on the map.
 * and centered position
 */
typedef struct s_pos
{
	double	x;
	double	y;
	int		x_screen;
	int		y_screen;
}	t_pos;

/**
 * @brief Stores the player's angle and rotation direction.
 */
typedef struct s_rot
{
	double	current_angle;
	bool	left;
	bool	right;
}	t_rot;

/**
 * @brief Stores player information, including direction, position, rotation
 * and movements.
 * 
 * @var face Initial direction ('N', 'W', 'E', or 'S').
 * @var speed pixel/tick
 * @var pos Player's position on the map.
 * @var rot Player's rotation details.
 * @var moving if player is moving forward or backward.
 * @var camera for player FOV and raycast projection.
 */
typedef struct s_player
{
	char		face;
	double		speed;
	double		rot_speed;
	t_pos		pos;
	t_rot		rot;
	t_moving	moving;
	t_camera	camera;
}	t_player;

#endif