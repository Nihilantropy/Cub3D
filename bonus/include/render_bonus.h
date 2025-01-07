
#ifndef RENDER_H
# define RENDER_H

# include "cub3D_bonus.h"

# define TEXTURE_SIZE 64
# define MAX_WALL_HEIGHT 1080
# define MIN_WALL_HEIGHT 20

typedef enum e_render_type
{
	static_render,
	dynamic_render
}	t_render_type;

typedef struct s_textures
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int		floor_color;
	int		ceiling_color;
	void	*floor;
	void	*ceiling;
    int		size;
}	t_textures;

typedef struct s_slice
{
	int		height;
	int		start_y;
	int		end_y;
	double	distance;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	int		side;
	void	*texture;
}	t_slice;

typedef struct s_render_state
{
	void	*img_ptr;
	int		*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
}	t_render_state;

#endif