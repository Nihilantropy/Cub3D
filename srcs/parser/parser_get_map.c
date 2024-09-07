#include "../include/cub3D.h"

static int	get_matrix_len(const char *map);
static bool	parse_matrix(t_game *game, char **matrix);
static bool	build_matrix(char **matrix, const char *map);

bool	get_map(t_game *game, const char *map)
{
	int		len;
	char	**matrix;

	len = get_matrix_len(map);
	if (!len)
	{
		ft_putstr_fd(ERR_EMPY_FILE, 2);
		return (false);
	}
	matrix = (char **)malloc(sizeof(char *) * (len + 1));
	if (!matrix)
		ft_exit_error(ERR_ALLOC_MATRIX);
	if (build_matrix(matrix, map) == false)
		return (false);
	if (check_valid_map(game, (const char **)matrix) == false)
		return (false);
	print_matrix(matrix);
	parse_matrix(game, matrix);
	free(matrix);
	return (true);
}

static bool	parse_matrix(t_game *game, char **matrix)
{
	//int	map_info_len;
	//int	map_matrix_len;

	if (!game || !matrix)
		return (1);
	//map_info_len = get_map_info_len(matrix);
	//map_matrix_len = get_map_matrix_len(matrix);
	return (0);
}

static bool	build_matrix(char **matrix, const char *map)
{
	char	*line;
	int		y;
	int		fd;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (false);
	}
	y = 0;
	while (line)
	{
		//printf("map line[%d] is: %s", y, line); 
		matrix[y] = ft_strdup(line);
		//printf("matrix[%d] is: %s\n", y, matrix[y]);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	matrix[y] = NULL;
	close(fd);
	return (true);
}

static int	get_matrix_len(const char *map)
{
	char	*line;
	int		y;
	int		fd;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	y = 0;
	while (line)
	{
		y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (y);
}