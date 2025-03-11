/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   212_check_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-bri <lude-bri@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:21:51 by luigi             #+#    #+#             */
/*   Updated: 2025/03/10 21:35:59 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_bottom(t_map *map, char **map_copy)
{
	int		x;
	int		y;
	bool	valid;

	(void)map;
	valid = true;
	y = 0;
	while (map_copy[y])
		y++;
	y -= 1;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x] == '#' && map_copy[y][x] != '\n' && map_copy[y][x])
			x++;
		if (map_copy[y][x] == '\n' || map_copy[y][x] == '\0')
			y--;
		else if (map_copy[y][x] == '1')
		{
			if (map_copy[y - 1][x] != '1')
				valid = false;
			while (map_copy[y][x] == '1' || map_copy[y][x] == '#')
				x++;
			if (valid == true)
				break ;
		}
	}
	if (valid == false)
		return (FAILURE);
	return (SUCCESS);
}

int	check_top(t_map *map, char **map_copy)
{
	int		y;
	int		x;
	bool	valid;

	(void)map;
	valid = true;
	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x] == '#' && map_copy[y][x] != '\n' && map_copy[y][x])
			x++;
		if (map_copy[y][x] == '\n' || map_copy[y][x] == '\0')
			y++;
		else if (map_copy[y][x] == '1')
		{
			if (map_copy[y + 1][x] != '1')
				valid = false;
			while (map_copy[y][x] == '1' || map_copy[y][x] == '#')
				x++;
			if (valid == true)
				break ;
		}
	}
	if (valid == false)
		return (FAILURE);
	return(SUCCESS);
}

int	check_sides(t_map *map, char **map_copy)
{
	int		x;
	int		y;
	bool	valid;

	(void)map;
	valid = true;
	y = 0;
	while (map_copy[y])
		y++;
	x = -1;
	while (++x < y)
	{
		if (map_copy[x][1] != '#' && map_copy[x][1] != '1')
			valid = false;
	}
	x = 0;
	y = 0;
	while (map_copy[y][x])
		x++;
	x--;
	while (map_copy[y])
	{
		if (map_copy[y][x - 1] != '#' && map_copy[y][x - 1] != '1')
			valid = false;
		y++;
	}
	if (valid == false)
		return (FAILURE);
	return(SUCCESS);
}

int	check_holes(t_map *map, char **map_copy)
{
	(void)map;
	(void)map_copy;
	return(SUCCESS);
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
