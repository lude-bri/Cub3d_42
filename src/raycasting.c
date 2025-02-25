/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:24:19 by mde-agui          #+#    #+#             */
/*   Updated: 2025/02/25 16:00:52 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(int x, int y, int color, t_data *data)
{
	int	i;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y <= 0)
		return ;
	i = y * data->img.line_length + x * data->img.bits_per_pixel / 8;
	data->data[i] = color & 0xFF;
	data->data[i + 1] = (color >> 8) & 0xFF;
	data->data[i + 2] = (color >> 16) & 0xFF;
}

bool	touch_obs(float px, float py, t_data *data)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (data->map->grid[y][x] == '1')
		return (true);
	return (false);
}

float	fixed_dist(float x1, float y1, float x2, t_data *data)
{
	float	dx;
	float	dy;
	float	angle;
	float	dist;

	dx = x2 - x1;
	dy = data->player.y - y1;
	angle = atan2(dy, dx) - data->player.angle;
	dist = (sqrt(dx * dx + dy * dy)) * cos(angle);
	return (dist);
}

void	draw_line(t_player *player, float angle, int i, t_data *data)
{
	float	ray_x;
	float	ray_y;
	float	dist;
	int		height;
	int		start;

	ray_x = player->x;
	ray_y = player->y;
	while (!touch_obs(ray_x, ray_y, data))
	{
		ray_x += cos(angle);
		ray_y += sin(angle);
		if (TWO_D)
			put_pixel(ray_x, ray_y, 0xFF0000, data);
	}
	if (!TWO_D)
	{
		dist = sqrt((ray_x - player->x) * (ray_x - player->x)
			+ (ray_y - player->y) * (ray_y - player->y));
		//dist = fixed_dist(player->x, player->y, ray_x, data);
		height = (BLOCK / dist) * (WIDTH / 2);
		start = (HEIGHT - height) / 2;
		while (start < (HEIGHT + height) / 2)
			put_pixel(i, start++, 255, data);
	}
}

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

	map = data->map->grid;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, data);
		}
	}
}

void	clear_image(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(x, y, 0, data);
	}
}

int	draw_loop(t_data *data)
{
	int		i;
	float	start_x;
	float	step;

	move_player(&data->player);
	clear_image(data);
	if (TWO_D)
	{
		draw_square(data->player.x, data->player.y, 10, data);
		draw_map(data);
	}
	step = PI / 3 / WIDTH;
	start_x = data->player.angle - PI / 6;
	i = -1;
	while (++i < WIDTH)
	{
		draw_line(&data->player, start_x, i, data);
		start_x += step;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
