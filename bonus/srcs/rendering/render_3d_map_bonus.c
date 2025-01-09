/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_map_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:08:33 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 12:08:34 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	render_static_textures(t_game *game, t_render_state *state);
static void	render_dynamic_textures(t_game *game, t_render_state *state);

void	render_3d_map(t_game *game, t_render_state *state)
{
	render_floor_ceiling(game, state);
	render_static_textures(game, state);
	render_dynamic_textures(game, state);
}

static void	render_static_textures(t_game *game, t_render_state *state)
{
	int		x;
	int		side;
	t_slice	slice;

	x = 0;
	side = -1;
	while (x < game->display.width)
	{
		side = cast_ray(game, &game->player, x, static_render);
		if (side == -1)
		{
			x++;
			continue ;
		}
		calculate_slice(&slice, game, game->player.camera.perp_dist);
		slice.side = side;
		calculate_texture_coords(&slice, game, &game->player.camera);
		slice.texture = get_texture(game, &game->player.camera, slice.side);
		render_textured_slice(state, &slice, game, x);
		x++;
	}
}

static void	render_dynamic_textures(t_game *game, t_render_state *state)
{
	int		x;
	int		side;
	t_slice	slice;

	x = 0;
	side = -1;
	while (x < game->display.width)
	{
		side = cast_ray(game, &game->player, x, dynamic_render);
		if (side == -1)
		{
			x++;
			continue ;
		}
		calculate_slice(&slice, game, game->player.camera.perp_dist);
		slice.side = side;
		calculate_texture_coords(&slice, game, &game->player.camera);
		slice.texture = get_texture(game, &game->player.camera, slice.side);
		render_transparent_slice(state, &slice, game, x);
		x++;
	}
}
