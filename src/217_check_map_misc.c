/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   217_check_map_misc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:24:07 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 17:27:26 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	find_bottom_line(char **map_copy)
{
	int	y;
	int	x;

	y = 0;
	while (map_copy[y])
		y++;
	y -= 1;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x] == '#'
			&& map_copy[y][x] != '\n' && map_copy[y][x])
			x++;
		if (map_copy[y][x] == '\n' || map_copy[y][x] == '\0')
			y--;
		else
			break ;
	}
	return (y);
}

int	find_top_line(char **map_copy)
{
	int	y;
	int	x;

	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x] == '#'
			&& map_copy[y][x] != '\n' && map_copy[y][x])
			x++;
		if (map_copy[y][x] == '\n' || map_copy[y][x] == '\0')
			y++;
		else
			break ;
	}
	return (y);
}

int	check_left_side(char **map_copy)
{
	int		y;
	int		max_y;
	bool	valid;

	valid = true;
	y = 0;
	while (map_copy[y])
		y++;
	max_y = y;
	y = 0;
	while (y < max_y)
	{
		if (map_copy[y][1] != '#' && map_copy[y][1] != '1')
			valid = false;
		y++;
	}
	if (valid == false)
		return (FAILURE);
	return (SUCCESS);
}

int	check_right_side(char **map_copy)
{
	int		x;
	int		y;
	bool	valid;

	valid = true;
	x = 0;
	y = 0;
	while (map_copy[y][x])
		x++;
	x--;
	y = 0;
	while (map_copy[y])
	{
		if (map_copy[y][x - 1] != '#' && map_copy[y][x - 1] != '1')
			valid = false;
		y++;
	}
	if (valid == false)
		return (FAILURE);
	return (SUCCESS);
}
