
#ifndef RENDER_H
# define RENDER_H

# include "cub3D.h"

// Wall rendering constants
# define TEXTURE_SIZE 64
# define MAX_WALL_HEIGHT 1080
# define MIN_WALL_HEIGHT 20

#define PATH_TO_NORHT_WALL_TEXTURE "texture/walls/north_wall_texture.xpm"
#define PATH_TO_SOUTH_WALL_TEXTURE "texture/walls/south_wall_texture.xpm"
#define PATH_TO_EAST_WALL_TEXTURE "texture/walls/east_wall_texture.xpm"
#define PATH_TO_WEST_WALL_TEXTURE "texture/walls/west_wall_texture.xpm"
#define PATH_TO_FLOOR_TEXTURE "texture/floor/floor_texture.xpm"
#define PATH_TO_CEILING_TEXTURE "texture/ceiling/ceiling_texture.xpm"
typedef struct s_textures
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	void	*floor;
	void	*ceiling;
    int		size;
}	t_textures;

typedef struct s_wall_slice
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
}	t_wall_slice;

typedef struct s_render_state {
	void	*img_ptr;
	int		*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_render_state;

#endif