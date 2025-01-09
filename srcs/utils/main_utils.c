/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:13:36 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 11:13:37 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_all_and_exit(t_game *game, int status)
{
	if (game)
	{
		if (game->win_ptr && game->mlx_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		free_matrix((char **)game->map.matrix);
		free_bool_matrix(game->map.check.visited);
		free_info_list(&game->map.check.info);
		free_textures(game);
		if (game->mlx_ptr)
		{
			mlx_destroy_display(game->mlx_ptr);
			free(game->mlx_ptr);
		}
	}
	exit(status);
}
