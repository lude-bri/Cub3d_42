/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   201_setters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-bri <lude-bri@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 23:46:43 by luigi             #+#    #+#             */
/*   Updated: 2025/02/27 23:52:23 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_whitespace(char line)
{
	return ((line == ' ') || (line == '\t'));
}

int	assign_path(char *line, char *id, char **target, t_data *data)
{
	char	*new_line;

	if (line[0] == id[0] && line[1] == id[1])
	{
		line += 2;
		while (is_whitespace(*line))
			line++;
		line = ft_strtrim(line, "\n");
		new_line = ft_strtrim(line, " ");
		if (*line && *new_line)
		{
			*target = ft_strdup(new_line);
			free(new_line);
			free(line);
			return (SUCCESS);
		}
		else
			error(PARSE, data);
	}
	return (FAILURE);
}

void	set_coord(char *line, t_game *game, t_data *data)
{
	if (assign_path(line, "NO", &game->north.path, data) == SUCCESS ||
		assign_path(line, "SO", &game->south.path, data) == SUCCESS ||
		assign_path(line, "WE", &game->west.path, data) == SUCCESS ||
		assign_path(line, "EA", &game->east.path, data) == SUCCESS)
	{
		return ;
	}
	else
		error(PARSE, data);
}

void	set_fc(char *line, t_game *game, t_data *data)
{
	char	**rgb;
	int		i;
	bool	fc; //floor is true - ceiling is false

	fc = false;
	if (*line == 'F')
		fc = true;
	line++;
	if (!is_whitespace(*line))
		error(PARSE, data);
	while (is_whitespace(*line))
		line++;
	if (line)
	{
		rgb = ft_split(line, ',');
		i = -1;
		while (++i <= 2)
			if (!rgb[i] || ft_strcmp(rgb[i], "\n") == 0)
				error(RGB, data);
		if (fc == true)
		{
			game->floor.r = ft_atoi(rgb[0]);
			game->floor.g = ft_atoi(rgb[1]);
			game->floor.b = ft_atoi(rgb[2]);
		}
		else
		{
			game->ceiling.r = ft_atoi(rgb[0]);
			game->ceiling.g = ft_atoi(rgb[1]);
			game->ceiling.b = ft_atoi(rgb[2]);
		}
		i = 0;
		while (rgb[i])
			free(rgb[i++]);
		free(rgb);
	}
	else
		error(PARSE, data);

}

int	set_map(char *line, t_map *map, t_data *data)
{
	static int	i = 0;

	if (!line)
		error(PARSE, data);
	if (!map->grid)
	{
		map->grid = malloc(sizeof(char *) * 1024);
		if (!map->grid)
			error(PARSE, data);
		ft_memset(map->grid, 0, sizeof(char *) * 1024);
	}
	map->grid[i++] = ft_strdup(line);
	return (SUCCESS);
}
