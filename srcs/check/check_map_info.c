#include "../include/cub3D.h"

static void	info_identifier_found(t_game *game, const char *line);
static bool	check_all_info_identifiers(t_info *info);

void	check_map_infos(t_game *game, const char **matrix)
{
	int		y;
	int		x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (matrix[y][x] && ft_isspace(matrix[y][x]))
			x++;
		if (matrix[y][x] == '\0')
		{
			y++;
			continue ;
		}
		if (is_info_line(matrix[y]))
			info_identifier_found(game, matrix[y]);
		y++;
	}
	print_info_list(game->map.check.info);
	if (check_all_info_identifiers(game->map.check.info) == true)
		game->map.check.map_infos = true;
}

static void	info_identifier_found(t_game *game, const char *line)
{
	t_info	*info;

	info = game->map.check.info;
	if (ft_strncmp(line, "NO ", 3) == 0)
		info->found = true;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		info->next->found = true;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		info->next->next->found = true;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		info->next->next->next->found = true;
	else if (ft_strncmp(line, "F ", 2) == 0)
		info->next->next->next->next->found = true;
	else if (ft_strncmp(line, "C ", 2) == 0)
		info->next->next->next->next->next->found = true;
	
}

static bool	check_all_info_identifiers(t_info *info)
{
	t_info	*current_node;

	current_node = info;
	while (current_node)
	{
		if (current_node->found == false)
			return (false);
		current_node = current_node->next;
	}
	return (true);
}