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

int	assign_path(char *line, char *id, char **target)
{
	if (line[0] == id[0] && line[1] == id[1])
	{
		line += 2;
		while (is_whitespace(*line))
			line++;
		if (*line)
		{
			*target = ft_strdup(line);
			return (SUCCESS);
		}
		else
			error(PARSE);
	}
	return (FAILURE);
}

void	set_coord(char *line, t_game *game)
{
	if (assign_path(line, "NO", &game->north.path) == SUCCESS ||
		assign_path(line, "SO", &game->south.path) == SUCCESS ||
		assign_path(line, "WE", &game->west.path) == SUCCESS ||
		assign_path(line, "EA", &game->east.path) == SUCCESS)
	{
		return ;
	}
	else
		error(PARSE);
}

void	set_fc(char *line, t_game *game)
{
	char	**rgb;
	bool	fc; //floor is true - ceiling is false

	fc = false;
	if (*line == 'F')
		fc = true;
	line++;
	if (!is_whitespace(*line))
		error(PARSE);
	while (is_whitespace(*line))
		line++;
	if (line)
	{
		rgb = ft_split(line, ',');
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
	}
	else
		error(PARSE);
}

int	set_map(char *line, t_map *map)
{
	static int	i = 0;

	if (!line)
		error(PARSE);
	if (!map->grid)
		map->grid = malloc(sizeof(char *) * 1024);
	if (!map->grid)
		error(PARSE);
	map->grid[i++] = line;
	return (SUCCESS);
}
