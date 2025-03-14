/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   212_check_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:21:51 by luigi             #+#    #+#             */
/*   Updated: 2025/03/14 18:39:48 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_holes(t_map *map, char **map_copy)
{
	int		x;
	int		y;
	bool	valid;

	(void)map;
	valid = true;
	y = -1;
	while (map_copy[++y])
	{
		x = 0;
		while (x < (int)ft_strlen(&map_copy[y][x]))
		{
			if (map_copy[y][x] == '0')
			{
				if (map_copy[y][x + 1] == '#' || map_copy[y][x - 1] == '#'
					|| map_copy[y + 1][x] == '#' || map_copy[y - 1][x] == '#')
					valid = false;
			}
			x++;
		}
	}
	if (valid == false)
		return (FAILURE);
	return (SUCCESS);
}

int	check_sides(t_map *map, char **map_copy)
{
	(void)map;
	if (check_left_side(map_copy) == FAILURE)
		return (FAILURE);
	if (check_right_side(map_copy) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_bottom(t_map *map, char **map_copy)
{
	int		x;
	int		y;
	bool	valid;

	(void)map;
	valid = true;
	y = find_bottom_line(map_copy);
	x = 0;
	while (map_copy[y][x] == '#' && map_copy[y][x] != '\n' && map_copy[y][x])
		x++;
	if (map_copy[y][x] == '1')
	{
		if (map_copy[y - 1][x] != '1')
			valid = false;
		while (map_copy[y][x] == '1' || map_copy[y][x] == '#')
			x++;
		if (valid == false)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	check_top(t_map *map, char **map_copy)
{
	int		y;
	int		x;
	bool	valid;

	(void)map;
	valid = true;
	y = find_top_line(map_copy);
	x = 0;
	while (map_copy[y][x] == '#' && map_copy[y][x] != '\n' && map_copy[y][x])
		x++;
	if (map_copy[y][x] == '1')
	{
		if (map_copy[y + 1][x] != '1')
			valid = false;
		while (map_copy[y][x] == '1' || map_copy[y][x] == '#')
			x++;
		if (valid == false)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	check_map(t_map *map, char **map_copy)
{
	if (!map->grid)
		return (FAILURE);
	if (!check_top(map, map_copy))
		return (FAILURE);
	if (!check_bottom(map, map_copy))
		return (FAILURE);
	if (!check_sides(map, map_copy))
		return (FAILURE);
	if (!check_holes(map, map_copy))
		return (FAILURE);
	return (SUCCESS);
}
