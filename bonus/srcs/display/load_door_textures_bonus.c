#include "../../include/cub3D_bonus.h"

static char	**init_door_path_texture(void);
static bool	check_door_texture_load(t_game *game, int width, int height);

bool	load_door_texture(t_game *game)
{
	char	**path;
	int		i;
	int		width;
	int		height;

	path = init_door_path_texture();
	i = 0;
	while (i < DOOR_FRAMES)
	{
		game->door_system.texture[i] = mlx_xpm_file_to_image(game->mlx_ptr,
			path[i], &width, &height);
		i++;
	}
	if (!check_door_texture_load(game, width, height))
	{
		free_matrix(path);
		return (ft_bool_putstr_fd(ERR_TEXTURE_LOAD_DOOR, 2));
	}
	free_matrix(path);
	return (true);
}

static char	**init_door_path_texture(void)
{
	char	**path;

	path = NULL;
	path = ft_calloc(DOOR_FRAMES + 1, sizeof(char *));
	if (!path)
		ft_exit_error(ERR_ALLOC_DOOR_PATH_MATRIX);
	path[0] = ft_strdup(DOOR_TEXTURE_1);
	path[1] = ft_strdup(DOOR_TEXTURE_2);
	path[2] = ft_strdup(DOOR_TEXTURE_3);
	path[3] = ft_strdup(DOOR_TEXTURE_4);
	path[4] = ft_strdup(DOOR_TEXTURE_5);
	path[5] = ft_strdup(DOOR_TEXTURE_6);
	path[6] = NULL;
	if (!path[0] || !path[1] || !path[2]
		|| !path[3] || !path[4] || !path[5])
		ft_exit_error(ERR_ALLOC_DOOR_PATH);
	return (path);
}

static bool	check_door_texture_load(t_game *game, int width, int height)
{
	int	i;

	i = 0;
	while (i < DOOR_FRAMES)
	{
		if (!game->door_system.texture[i] || width != TEXTURE_SIZE || 
			height != TEXTURE_SIZE)
			return (false);
		i++;
	}
	return (true);
}