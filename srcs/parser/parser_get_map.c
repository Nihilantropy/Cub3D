#include "../include/cub3D.h"

static int	get_matrix_len(const char *map);
static bool	build_matrixes(t_game *game, char **matrix, const char *map);

/** 
 * @brief get map:
 * 1) build 2 matrixes: first one is a copy
 * of the file provided by the user;
 * second one is only the map matrix,
 * filled with FILLER CHAR ('H'), to
 * make controls easier
 * 2) do all the necessary checks:
 * - info validation
 * - map matrix validation
 */
bool	get_map(t_game *game, const char *map)
{
	bool	flag;
	int		len;
	char	**matrix;

	matrix = NULL;
	len = get_matrix_len(map);
	if (!len)
	{
		ft_putstr_fd(ERR_EMPY_FILE, 2);
		return (false);
	}
	matrix = (char **)malloc(sizeof(char *) * (len + 1));
	if (!matrix)
		ft_exit_error(ERR_ALLOC_MATRIX);
	if (build_matrixes(game, matrix, map) == false)
		flag = false;
	else if (check_valid_map(game, (const char **)matrix) == false)
		flag = false;
	else
		flag = true;
	free_matrix(matrix);

	printf("DEBUG: Exiting get_map with size: width=%d, height=%d\n",
        game->map.width, game->map.height);
	return (flag);
}

static bool	build_matrixes(t_game *game, char **matrix, const char *map)
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
	if (parse_matrix(game, (const char **)matrix) == false)
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
