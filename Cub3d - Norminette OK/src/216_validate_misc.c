/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   216_validate_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:20:13 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 18:11:22 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_map_cell(t_map *map, int x, int y, int *player_count)
{
	if (map->grid[y][x] != ' ' && map->grid[y][x] != '0'
		&& map->grid[y][x] != '1' && map->grid[y][x] != '\n')
	{
		if (!verify_player(map, map->grid[y][x], (*player_count)++))
			return (FAILURE);
		else
		{
			map->player_x = x;
			map->player_y = y;
		}
	}
	return (SUCCESS);
}

static void	transform_map(char **map, int w)
{
	int		x;
	int		y;
	char	*temp;

	y = 0;
	while (map[y])
	{
		x = 0;
		temp = malloc(w + 1);
		if (!temp)
			exit(EXIT_FAILURE);
		ft_memset(temp, '#', w);
		temp[w] = '\0';
		while (map[y][x] && map[y][x] != '\n' && x < w)
		{
			if (map[y][x] != ' ')
				temp[x] = map[y][x];
			x++;
		}
		free(map[y]);
		map[y] = temp;
		y++;
	}
	map[y] = NULL;
}

static char	*create_border_line(int width)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (width + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (++i < width)
		line[i] = '#';
	line[i] = '\0';
	return (line);
}

static char	**initialize_map_structure(int new_height, int new_width)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (new_height + 1));
	if (!map_copy)
		return (NULL);
	map_copy[0] = create_border_line(new_width);
	if (!map_copy[0])
		return (NULL);
	i = 0;
	while (++i < new_height - 1)
	{
		map_copy[i] = malloc(sizeof(char) * (new_width + 1));
		if (!map_copy[i])
			return (NULL);
	}
	map_copy[new_height - 1] = create_border_line(new_width);
	if (!map_copy[new_height - 1])
		return (NULL);
	map_copy[new_height] = NULL;
	return (map_copy);
}

char	**copy_map(t_map *map)
{
	char	**map_copy;
	int		i;
	int		new_height;
	int		new_width;

	new_height = map->height + 2;
	new_width = map->width + 2;
	map_copy = initialize_map_structure(new_height, new_width);
	if (!map_copy)
		return (NULL);
	i = -1;
	while (++i < map->height)
	{
		map_copy[i + 1][0] = '#';
		ft_strlcpy(&map_copy[i + 1][1], map->grid[i], map->width + 1);
	}
	transform_map(map_copy, new_width);
	return (map_copy);
}
