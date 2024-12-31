#include "../include/cub3D.h"

static void calculate_wall_slice(t_wall_slice *slice, t_game *game, 
    double perp_wall_dist)
{
    slice->height = (int)(game->display.height / perp_wall_dist);
    slice->start_y = -slice->height / 2 + game->display.height / 2;
    slice->end_y = slice->height / 2 + game->display.height / 2;
    
    if (slice->start_y < 0)
        slice->start_y = 0;
    if (slice->end_y >= game->display.height)
        slice->end_y = game->display.height - 1;
}

static void select_wall_texture(t_wall_slice *slice, t_game *game, t_camera *cam)
{
    if (cam->ray_dir_y > 0 && slice->side == 1)
        slice->texture = game->textures.south;  // Hit south face
    else if (cam->ray_dir_y <= 0 && slice->side == 1)
        slice->texture = game->textures.north;  // Hit north face
    else if (cam->ray_dir_x > 0 && slice->side == 0)
        slice->texture = game->textures.east;   // Hit east face
    else
        slice->texture = game->textures.west;   // Hit west face
}

static void draw_textured_wall_slice(t_render_state *state, t_wall_slice *slice, 
    t_game *game, int x)
{
    int y;
    double step;
    double tex_pos;
    int tex_y;
    int color;
    int *texture_data;
    int bits_per_pixel;
    int line_length;
    int endian;

    // Get texture data
    if (!slice->texture)
    {
        printf("Error: Null texture for wall slice\n");
        return;
    }

    texture_data = (int *)mlx_get_data_addr(slice->texture, &bits_per_pixel,
        &line_length, &endian);
    if (!texture_data)
    {
        printf("Error: Failed to get texture data\n");
        return;
    }

    // Calculate texture step for vertical mapping
    step = 1.0 * TEXTURE_SIZE / slice->height;
    tex_pos = (slice->start_y - game->display.height / 2 + slice->height / 2) * step;

    // Draw the textured wall slice
    y = slice->start_y;
    while (y < slice->end_y)
    {
        tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
        tex_pos += step;

        // Get color from texture
        color = texture_data[TEXTURE_SIZE * tex_y + slice->tex_x];
        
        // Apply shading for sides
        if (slice->side == 1)
            color = (color >> 1) & 8355711;

        // Draw pixel
        if (y * game->display.width + x >= 0 && 
            y * game->display.width + x < game->display.width * game->display.height)
        {
            state->img_data[y * game->display.width + x] = color;
        }
        y++;
    }
}

static void calculate_texture_coords(t_wall_slice *slice, t_game *game, t_camera *cam)
{
    // Calculate wall X coordinate (where exactly the wall was hit)
    if (slice->side == 0)
        slice->wall_x = game->player.pos.y + cam->perp_wall_dist * cam->ray_dir_y;
    else
        slice->wall_x = game->player.pos.x + cam->perp_wall_dist * cam->ray_dir_x;
    slice->wall_x -= floor(slice->wall_x);

    // Calculate texture X coordinate
    slice->tex_x = (int)(slice->wall_x * TEXTURE_SIZE);
    if (slice->side == 0 && cam->ray_dir_x > 0)
        slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
    if (slice->side == 1 && cam->ray_dir_y < 0)
        slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
}

void render_walls(t_game *game, t_render_state *state, int x)
{
    t_wall_slice slice;
    
	cast_ray(game, &game->player, x);
	
	// Calculate wall properties
	calculate_wall_slice(&slice, game, game->player.camera.perp_wall_dist);
	slice.side = game->player.camera.side;
	slice.distance = game->player.camera.perp_wall_dist;
	
	// Get texture coordinates and select texture
	calculate_texture_coords(&slice, game, &game->player.camera);
	select_wall_texture(&slice, game, &game->player.camera);
	
	// Draw the textured wall slice
	draw_textured_wall_slice(state, &slice, game, x);
}