#ifndef KEYS_H
# define KEYS_H

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3

# define X_MOUSE_PRESS 4
# define X_MOUSE_RELEASE 5

# define DESTROY_WIN_CLIENT_MSG 17

# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_FORWARD 	65362
# define KEY_BACKWARD	65364
# define KEY_SPACE		32

# define MOUSE_LEFT		1
# define MOUSE_RIGHT	3

# define KEY_ESC		65307

typedef struct s_keys
{
	bool	w_pressed;
	bool	s_pressed;
	bool	a_pressed;
	bool	d_pressed;
	bool	left_pressed;
	bool	right_pressed;
	bool	space_pressed;
}	t_keys;

#endif