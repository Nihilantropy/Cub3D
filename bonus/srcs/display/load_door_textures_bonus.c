/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_door_textures_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crea <crea@student.42roma.it>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:45:34 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 15:49:39 by crea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

static void	init_door_textures(t_door_system *door_system);
static bool	generate_frames(t_game *game, t_render_state *orig_data,
				int width);
static bool	create_frame(t_game *game, t_render_state *orig_data,
				int frame, int width);
static void	fill_frame_pixels(t_render_state *tex_data,
				t_render_state *orig_data, int width, int offset);

/**
 * @brief Loads door texture and generates all animation frames
 * Creates a sequence of textures showing the door sliding open
 *
 * @param game Game structure containing door system data
 * @return bool true if door textures loaded successfully, false otherwise
 */
bool	load_door_texture(t_game *game)
{
	t_render_state	orig_data;
	int				width;
	int				height;
	
	init_door_textures(&game->door_system);
	orig_data.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, DOOR_TEXTURE_1,
			&width, &height);
	if (!orig_data.img_ptr)
		return (false);
	orig_data.img_data = (int *)mlx_get_data_addr(orig_data.img_ptr,
			&orig_data.bits_per_pixel, &orig_data.line_length,
			&orig_data.endian);
	if (!generate_frames(game, &orig_data, width))
	{
		mlx_destroy_image(game->mlx_ptr, orig_data.img_ptr);
		return (false);
	}
	mlx_destroy_image(game->mlx_ptr, orig_data.img_ptr);
	return (true);
}

static void	init_door_textures(t_door_system *door_system)
{
	int	i;

	door_system->texture = malloc(sizeof(void *) * DOOR_FRAME);
	if (!door_system)
		ft_exit_error(ERR_ALLOC_DOOR_TEXTURES);
	i = 0;
	while (i < DOOR_FRAME)
		door_system->texture[i++] = NULL;
}

/**
 * @brief Generates all frames for the door animation sequence
 *
 * @param game Game structure containing door system data
 * @param orig_data Original door texture data
 * @param width Width of the texture
 * @return bool true if all frames generated successfully, false otherwise
 */
static bool	generate_frames(t_game *game, t_render_state *orig_data, int width)
{
	int	frame;

	frame = 0;
	while (frame < DOOR_FRAME)
	{
		if (!create_frame(game, orig_data, frame, width))
			return (false);
		frame++;
	}
	return (true);
}

/**
 * @brief Creates a single frame of the door animation sequence
 *
 * @param game Game structure containing MLX data
 * @param orig_data Original door texture data
 * @param frame Current frame number being generated
 * @param width Width of the texture
 * @return bool true if frame created successfully, false otherwise
 */
static bool	create_frame(t_game *game, t_render_state *orig_data,
				int frame, int width)
{
	t_render_state	tex_data;
	int				offset;

	tex_data.img_ptr = mlx_new_image(game->mlx_ptr, width, TEXTURE_SIZE);
	if (!tex_data.img_ptr)
		return (false);
	tex_data.img_data = (int *)mlx_get_data_addr(tex_data.img_ptr,
			&tex_data.bits_per_pixel, &tex_data.line_length, &tex_data.endian);
	offset = (width * frame) / (DOOR_FRAME - 1);
	fill_frame_pixels(&tex_data, orig_data, width, offset);
	game->door_system.texture[frame] = tex_data.img_ptr;
	return (true);
}

/**
 * @brief Fills new frame pixels with offset door texture or transparency
 *
 * @param tex_data New frame texture data
 * @param orig_data Original door texture data
 * @param width Width of the texture
 * @param offset X-offset for sliding door effect
 */
static void	fill_frame_pixels(t_render_state *tex_data,
				t_render_state *orig_data, int width, int offset)
{
	int	x;
	int	y;
	int	src_x;

	y = 0;
	while (y < TEXTURE_SIZE)
	{
		x = 0;
		while (x < TEXTURE_SIZE)
		{
			src_x = x + offset;
			if (src_x >= width)
				tex_data->img_data[y * width + x] = TRANSPARENT;
			else
				tex_data->img_data[y * width + x]
					= orig_data->img_data[y * width + src_x];
			x++;
		}
		y++;
	}
}
