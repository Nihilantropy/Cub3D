#include "../include/cub3D.h"

void calculate_wall_slice(t_wall_slice *slice, t_game *game, 
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

void select_wall_texture(t_wall_slice *slice, t_game *game, t_camera *cam)
{
	if (cam->ray_dir_y > 0 && slice->side == 1)
		slice->texture = game->textures.south;
	else if (cam->ray_dir_y <= 0 && slice->side == 1)
		slice->texture = game->textures.north;
	else if (cam->ray_dir_x > 0 && slice->side == 0)
		slice->texture = game->textures.east;
	else
		slice->texture = game->textures.west;
}

void calculate_texture_coords(t_wall_slice *slice, t_game *game, t_camera *cam)
{
	if (slice->side == 0)
		slice->wall_x = game->player.pos.y + cam->perp_wall_dist * cam->ray_dir_y;
	else
		slice->wall_x = game->player.pos.x + cam->perp_wall_dist * cam->ray_dir_x;
	slice->wall_x -= floor(slice->wall_x);
	slice->tex_x = (int)(slice->wall_x * TEXTURE_SIZE);
	if (slice->side == 0 && cam->ray_dir_x > 0)
		slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
	if (slice->side == 1 && cam->ray_dir_y < 0)
		slice->tex_x = TEXTURE_SIZE - slice->tex_x - 1;
}
