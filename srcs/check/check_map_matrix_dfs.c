#include "../include/cub3D.h"

static bool	is_valid_cell(const char **matrix, int y, int x);
static bool	**create_bool_matrix(t_game *game, const char **matrix);
static void	dfs_mark_region(const char **matrix, bool **visited, int y, int x);

/*	check map island:
**	1) create a boolean matrix to mark the visited cells
**	2) 
*/
void	check_map_matrix_island(t_game *game, const char **matrix)
{
	int		y;
	int		x;

	y = 0;
	game->map.check.visited = create_bool_matrix(game, matrix);
	while (y < game->map.height)
	{
		x = 0;
		while (matrix[y][x])
		{
			if (is_valid_cell(matrix, y, x) &&
				!game->map.check.visited[y][x])
			{
				if (game->map.check.found_region)
				{
					game->map.check.map_island = true;
					break ;
				}
				dfs_mark_region(matrix, game->map.check.visited, y, x);
				game->map.check.found_region = true;
			}
			x++;
		}
		y++;
	}
}

static bool	**create_bool_matrix(t_game *game, const char **matrix)
{
	bool	**visited;
	int		y;
	
	visited = malloc(sizeof(bool *) * (game->map.height + 1));
	if (!visited)
		ft_exit_error(ERR_ALLOC_BOOL_MATRIX);
	y = 0;
	while (y < game->map.height)
	{
		visited[y] = malloc(sizeof(bool) * ft_strlen(matrix[y]));
		if (!visited[y])
			ft_exit_error(ERR_ALLOC_BOOL_MATRIX);
		ft_memset(visited[y], 0, sizeof(bool) * ft_strlen(matrix[y]));
		y++;
	}
	visited[y] = NULL;
	return (visited);
}

static bool	is_valid_cell(const char **matrix, int y, int x)
{
	return (y >= 0 &&
			x >= 0 &&
			matrix[y] != NULL &&
			matrix[y][x] != '\0' &&
			matrix[y][x] != SPACE &&
			matrix[y][x] != TAB &&
			matrix[y][x] != MAP_FILLER);
}

/*	dfs mark region:
**	use a dfs (Depth-First Search) algorithm to
**	identify isolated portions of map
*/
static void	dfs_mark_region(const char **matrix, bool **visited, int y, int x)
{
	if (!is_valid_cell(matrix, y, x) || visited[y][x])
		return ;
	visited[y][x] = true;
	dfs_mark_region(matrix, visited, y - 1, x);
	dfs_mark_region(matrix, visited, y + 1, x);
	dfs_mark_region(matrix, visited, y, x - 1);
	dfs_mark_region(matrix, visited, y, x + 1);
}
