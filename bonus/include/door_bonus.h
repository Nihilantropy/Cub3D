#ifndef DOOR_BONUS_H
# define DOOR_BONUS_H

# include "cub3D_bonus.h"

# define DOOR_FRAMES 6
# define DOOR_ANIM_SPEED 8

# define DOOR_TEXTURE_1 "./texture/door/door_texture_1.xpm"
# define DOOR_TEXTURE_2 "./texture/door/door_texture_2.xpm"
# define DOOR_TEXTURE_3 "./texture/door/door_texture_3.xpm"
# define DOOR_TEXTURE_4 "./texture/door/door_texture_4.xpm"
# define DOOR_TEXTURE_5 "./texture/door/door_texture_5.xpm"
# define DOOR_TEXTURE_6 "./texture/door/door_texture_6.xpm"

typedef enum e_door_state
{
	door_closed = 0,
	door_opening,
	door_open,
	door_closing
}	t_door_state;

typedef struct s_door
{
	t_pos			pos;
	t_door_state	state;
	int				frame;
	int				anim_counter;
	double			open_percentage;
	bool			active;
}	t_door;

typedef struct s_door_system
{
	void	*texture[DOOR_FRAMES];
	t_door	*door;
	int		door_counter;
}	t_door_system;

#endif