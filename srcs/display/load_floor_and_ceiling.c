#include "../include/cub3D.h"

static bool check_rgb_values(const char **rgb);
static int create_rgb(const char **rgb);
static bool process_rgb_values(int *color, char **values);
static bool create_solid_color_texture(t_game *game, void **texture, int color);
static bool	load_color_texture(t_game *game, char identifier, 
							int *color_ptr, void **texture);

bool load_floor_and_ceiling(t_game *game)
{
	if (!load_color_texture(game, 'F', &game->textures.floor_color,
						&game->textures.floor))
		return (ft_bool_putstr_fd(ERR_LOAD_FLOOR_RGB, 2));
	if (!load_color_texture(game, 'C', &game->textures.ceiling_color,
						&game->textures.ceiling))
		return (ft_bool_putstr_fd(ERR_LOAD_CEILING_RGB, 2));
	return (true);
}


static bool load_color_texture(t_game *game, char identifier, 
							int *color_ptr, void **texture)
{
	char	*rgb_str;
	char	**rgb_values;
	bool	success;

	rgb_str = find_texture_path(game->map.check.info, identifier);
	if (!rgb_str)
		return (false);
	rgb_values = ft_split(rgb_str, ',');
	free(rgb_str);
	if (!rgb_values)
		return (false);
	success = process_rgb_values(color_ptr, rgb_values);
	if (!success)
		return (false);
	return (create_solid_color_texture(game, texture, *color_ptr));
}


static bool	create_solid_color_texture(t_game *game, void **texture, int color)
{
	int	x;
	int	y;
	int	*data;
	int	bits_pp;
	int	line_len;
	int	endian;

	*texture = mlx_new_image(game->mlx_ptr, TEXTURE_SIZE, TEXTURE_SIZE);
	if (!(*texture))
		return (false);
	data = (int *)mlx_get_data_addr(*texture, &bits_pp, &line_len, &endian);
	y = 0;
	while (y < TEXTURE_SIZE)
	{
		x = 0;
		while (x < TEXTURE_SIZE)
		{
			data[y * (line_len / 4) + x] = color;
			x++;
		}
		y++;
	}
	return (true);
}

static bool process_rgb_values(int *color, char **values)
{
	if (!check_rgb_values((const char **)values))
	{
		free_matrix(values);
		return (false);
	}
	*color = create_rgb((const char **)values);
	free_matrix(values);
	return (true);
}

static bool check_rgb_values(const char **rgb)
{
	int	value;
	int	i;

	if (!rgb || matrix_len(rgb) != 3)
		return (false);
	i = 0;
	while (rgb[i])
	{
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			return (false);
		i++;
	}
	return (true);
}

static int create_rgb(const char **rgb)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	return ((r << 16) | (g << 8) | b);
}

