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

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/**
 * @brief Stores raycasting infos .
 */
typedef struct s_camera
{
	double	fov;
}	t_camera;


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
 */
typedef struct s_pos
{
	double	x;
	double	y;
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