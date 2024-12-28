
#ifndef RENDER_H
# define RENDER_H

# include "cub3D.h"

// Wall rendering constants
# define TEXTURE_SIZE 64
# define MAX_WALL_HEIGHT 1080
# define MIN_WALL_HEIGHT 20

typedef struct s_wall_slice {
    int     height;         // Height of wall slice
    int     start_y;        // Starting Y coordinate to draw
    int     end_y;         // Ending Y coordinate to draw
    double  distance;       // Distance to wall
    int     tex_x;         // X coordinate in texture
    int     side;          // Wall side (N,S,E,W)
} t_wall_slice;

typedef struct s_render_state {
    void    *img_ptr;      // Current frame buffer
    int     *img_data;     // Direct pixel access array
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_render_state;

#endif