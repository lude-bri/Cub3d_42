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

int	check_holes(char **map_copy)
{
	int		x;
	int		y;
	bool	valid;

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

int	check_sides(char **map_copy)
{
	if (check_left_side(map_copy) == FAILURE)
		return (FAILURE);
	if (check_right_side(map_copy) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_bottom(char **map_copy)
{
	int		x;
	int		y;
	bool	valid;

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
		if (map_copy[y][x] == 'N' || map_copy[y][x] == 'S'
			|| map_copy[y][x] == 'E' || map_copy[y][x] == 'W')
		{
			if (map_copy[y - 1][x] == '#' || map_copy[y + 1][x] == '#')
				return (FAILURE);
		}
		if (valid == false)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	check_top(char **map_copy)
{
	int		y;
	int		x;
	bool	valid;

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
		if (map_copy[y][x] == 'N' || map_copy[y][x] == 'S'
			|| map_copy[y][x] == 'E' || map_copy[y][x] == 'W')
		{
			if (map_copy[y - 1][x] == '#' || map_copy[y + 1][x] == '#')
				return (FAILURE);
		}
		if (valid == false)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	check_map(t_map *map, char **map_copy)
{
	(void)map;
	if (!map->grid)
		return (FAILURE);
	if (!check_top(map_copy))
		return (FAILURE);
	if (!check_bottom(map_copy))
		return (FAILURE);
	if (!check_sides(map_copy))
		return (FAILURE);
	if (!check_holes(map_copy))
		return (FAILURE);
	return (SUCCESS);
}
