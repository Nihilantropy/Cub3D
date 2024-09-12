#include "../include/cub3D.h"

static int	get_matrix_len(const char *map);
static bool	parse_matrix(t_game *game, char **matrix);
static bool	build_matrix(t_game *game, char **matrix, const char *map);


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
	if (build_matrix(game, matrix, map) == false)
		return (false);
	free_matrix(matrix);
	if (check_valid_map(game, game->map.matrix) == false)
		return (false);
	return (true);
}

static bool	build_matrix(t_game *game, char **matrix, const char *map)
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
		matrix[y] = ft_strtrim(line, "\r\v\n");
		free(line);
		line = get_next_line(fd);
		y++;
	}
	matrix[y] = NULL;
	close(fd);
	if (parse_matrix(game, matrix) == false)
		return (false);
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
