#ifndef PLAYER_H
# define PLAYER_H

# include <stdbool.h>

/* Movement and rotation constants */
# define P_SPEED 0.2
# define R_SPEED 0.1

/* player hitbox radius for wall collision */
# define PLAYER_RADIUS 0.2

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

typedef enum e_moving
{
	m_forward,
	m_backward,
	m_left,
	m_right,
	m_still
}	t_moving;

typedef enum e_rotating
{
	r_left,
	r_right,
	r_still
}	t_rotating;

/**
 * @brief Player structure containing all player-related data including
 * position, movement state, camera information and speeds
 */
typedef struct s_player
{
	t_pos		pos;
	t_moving	moving;
	t_rotating	rotating;
	t_camera	camera;
	double		speed;
	double		rot_speed;
	char		face;
}	t_player;

#endif