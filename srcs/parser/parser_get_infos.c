#include "../include/cub3D.h"

static char	*parse_info_content(const char *line);
static char	*parse_line(const char *line);
static char	*process_line_content(const char *line, char *new_line, int *i, int *j);

bool	parse_info(t_game *game, t_info *info, const char *line)
{
	char	*parsed_line;

	parsed_line = NULL;
	info->found = true;
	parsed_line = parse_info_content(line);
	if (!parsed_line)
		return (false);
	if (info->content)
	{
		game->map.check.wrong_info_nbr = true;
		return (false);
	}
	info->content = parsed_line;
	return (true);
}

static char	*parse_info_content(const char *line)
{
	char    **matrix;
	char    *content;
	char    *parsed_line;

	if (!line)
		return (NULL);
	parsed_line = parse_line(line);
	if (!parsed_line)
		return (NULL);
	matrix = ft_split(parsed_line, SPACE);
	free(parsed_line);
	if (!matrix)
		return (NULL);
	print_matrix((const char **)matrix);
	if (matrix_len((const char **)matrix) != 2)
	{
		free_matrix(matrix);
		return (NULL);
	}
	content = ft_strdup(matrix[1]);
	free_matrix(matrix);
	if (!content)
		return (NULL);
	return (content);
}

static char	*process_line_content(const char *line, char *new_line, int *i, int *j)
{
	bool	word_started;

	word_started = false;
	while (line[*i] && (line[*i] == SPACE || line[*i] == TAB))
		(*i)++;
	while (line[*i])
	{
		if (line[*i] == SPACE || line[*i] == TAB)
		{
			if (word_started)
			{
				new_line[(*j)++] = SPACE;
				word_started = false;
			}
		}
		else
		{
			new_line[(*j)++] = line[*i];
			word_started = true;
		}
		(*i)++;
	}
	return (new_line);
}

static char	*parse_line(const char *line)
{
	char	*new_line;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	new_line = process_line_content(line, new_line, &i, &j);
	if (j > 0 && new_line[j - 1] == SPACE)
		j--;
	new_line[j] = '\0';
	return (new_line);
}
