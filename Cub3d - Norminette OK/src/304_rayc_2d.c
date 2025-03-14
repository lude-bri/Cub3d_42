/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   304_rayc_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:45:42 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 18:55:50 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_square(int x, int y, int size, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			put_pixel(x + i, y + j, 0x0000FF, data);
	}
}

void	draw_map(t_data *data)
{
	char	**map;
	int		y;
	int		x;

	map = data->game->map.grid;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && map[y][x] != '\n')
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, data);
		}
	}
}
