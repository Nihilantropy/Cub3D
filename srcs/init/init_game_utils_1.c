#include "../include/cub3D.h"

static void		append_info_node(t_info **info, t_info *new_node);
static t_info	*find_last_info_node(t_info *info);
static char		set_info_identifier(int	i);

/** 
 * @brief init info list:
 * initialize a list with all
 * the necessary information
 * that the user should provide
 * in the map file
 */
void	init_info_list(t_game *game)
{
	t_info	**info;
	t_info	*new_node;
	int		i;

	info = &game->map.check.info;
	i = 0;
	while (i < 6)
	{
		new_node = malloc(sizeof(t_info));
		if (!new_node)
			ft_exit_error(ERR_ALLOC_INFO);
		new_node->identifier = set_info_identifier(i);
		new_node->content = NULL;
		new_node->found = false;
		new_node->index = -1;
		append_info_node(info, new_node);
		i++;
	}
}

static char	set_info_identifier(int	i)
{
	if (i == 0)
		return ('N');
	else if (i == 1)
		return ('S');
	else if (i == 2)
		return ('E');
	else if (i == 3)
		return ('W');
	else if (i == 4)
		return ('F');
	else if (i == 5)
		return ('C');
	return (0);	
}

static void append_info_node(t_info **info, t_info *new_node)
{
	t_info	*last_node;

	if (!new_node)
		return ;
	if (!*info)
		*info = new_node;
	else
	{
		last_node = find_last_info_node(*info);
		last_node->next = new_node;
	}
	new_node->next = NULL;
}

static t_info   *find_last_info_node(t_info *info)
{
	while (info->next)
		info = info->next;
	return (info);
}
