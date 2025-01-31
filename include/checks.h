/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcantell <mcantell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:37:54 by mcantell          #+#    #+#             */
/*   Updated: 2025/01/09 10:38:31 by mcantell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKS_H
# define CHECKS_H

/* enum for map tiles symbols */
typedef enum e_tiles
{
	FLOOR = '0',
	WALL = '1',
	NORTH = 'N',
	SOUTH = 'S',
	EAST = 'E',
	WEST = 'W',
	MAP_FILLER = 'H',
	SPACE = ' ',
	TAB = '\t',
}	t_tiles;

/* keep track of the necessary map infos */
typedef struct s_info
{
	char			identifier;
	bool			found;
	int				index;
	char			*content;
	struct s_info	*next;
}	t_info;

/* checks for map validation */
typedef struct s_check
{
	bool	wrong_char;
	bool	wrong_info_char;
	bool	wrong_info_nbr;
	bool	map_started;
	bool	map_order;
	bool	map_infos_id;
	bool	map_infos_cont;
	bool	**visited;
	bool	map_island;
	bool	found_region;
	bool	map_open;
	int		player;
	bool	map_matrix;
	int		map_start_row;
	t_info	*info;
}	t_check;

#endif
