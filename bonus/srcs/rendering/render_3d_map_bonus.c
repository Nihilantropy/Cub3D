#include "../../include/cub3D_bonus.h"



void render_3d_map(t_game *game, t_render_state *state, int x)
{
    t_wall_slice slice;
    
    cast_ray(game, &game->player, x);
    
    // Always render what's behind the door first
    calculate_wall_slice(&slice, game, game->player.camera.perp_wall_dist);
    slice.side = game->player.camera.side;
    calculate_texture_coords(&slice, game, &game->player.camera);
    slice.texture = get_texture(game, &game->player.camera, slice.side);
    render_textured_wall_slice(state, &slice, game, x);

    // Then overlay door if hit
    if (game->player.camera.door_hit)
    {
        calculate_wall_slice(&slice, game, game->player.camera.perp_door_dist);
        slice.texture = game->door_system.texture[game->player.camera.door_frame];
        render_transparent_slice(state, &slice, game, x);
    }
}
