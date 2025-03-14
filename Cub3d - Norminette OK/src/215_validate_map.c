/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   215_validate_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:15:05 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 18:45:24 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	validate_walls(t_map *map)
{
	char	**map_copy;
	int		i;

	map_copy = copy_map(map);
	i = -1;
	if (!map_copy)
		return (FAILURE);
	if (map->player_x < 0 || map->player_x >= map->width
		|| map->player_y < 0 || map->player_y >= map->height)
	{
		i = -1;
		while (map_copy[++i])
			free(map_copy[i]);
		free(map_copy);
		return (FAILURE);
	}
	if (!check_map(map, map_copy))
		return (FAILURE);
	i = 0;
	while (map_copy[i])
		free(map_copy[i++]);
	free(map_copy);
	return (SUCCESS);
}

static int	check_map_structure(t_map *map, int y)
{
	if (y >= map->height)
		return (FAILURE);
	if (map->grid[y] == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	validate_rows(t_map *map, int y, t_data *data)
{
	int	x;
	int	player_count;

	player_count = 0;
	if (check_map_structure(map, y) == FAILURE)
		return (FAILURE);
	while (map->grid[y])
	{
		x = -1;
		while (map->grid[y][++x] != '\n')
		{
			if (check_map_cell(map, x, y, &player_count) == FAILURE)
				return (FAILURE);
		}
		y++;
	}
	if (player_count != 1)
		error(PLAYER, data);
	return (SUCCESS);
}

int	set_map_coord(t_map *map)
{
	int		x;
	int		y;
	int		max_width;

	y = 0;
	if (!map->grid)
		return (FAILURE);
	while (map->grid[y])
		y++;
	map->height = y;
	y = 0;
	max_width = 0;
	while (map->grid[y])
	{
		x = 0;
		if (map->grid[y][x] == '\t')
			return (FAILURE);
		while (map->grid[y][x] && map->grid[y][x] != '\n')
			x++;
		if (x > max_width)
			max_width = x;
		y++;
	}
	map->width = max_width;
	return (SUCCESS);
}

int	validate_map(t_map *map, t_data *data)
{
	if (!set_map_coord(map))
		return (FAILURE);
	if (map->width <= 0 || map->height <= 0 || map->grid == NULL)
		return (FAILURE);
	if (!validate_rows(map, 0, data))
		return (FAILURE);
	if (!validate_walls(map))
		return (FAILURE);
	return (SUCCESS);
}
