#include "../../include/cub3D_bonus.h"

void render_3d_map(t_game *game, t_render_state *state, int x)
{
    t_wall_slice    slice;
    t_wall_slice    door_slice;
    
    cast_ray(game, &game->player, x);
    
    calculate_wall_slice(&slice, game, game->player.camera.perp_wall_dist);
    slice.side = game->player.camera.side;
    calculate_texture_coords(&slice, game, &game->player.camera);
    slice.texture = get_texture(game, &game->player.camera, slice.side);
    render_textured_wall_slice(state, &slice, game, x);

    if (game->player.camera.door_hit)
    {
        calculate_wall_slice(&door_slice, game, game->player.camera.perp_door_dist);
        door_slice.side = game->player.camera.door_side;
        calculate_texture_coords(&door_slice, game, &game->player.camera);
        door_slice.texture = game->door_system.texture[game->player.camera.door_frame];
        render_transparent_slice(state, &door_slice, game, x);
    }
}
