/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:24:19 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 19:24:53 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	touch_obs(float px, float py, t_data *data)
{
	int	x;
	int	y;

	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (y < 0 || y >= data->game->map.height || x < 0
		|| x >= (int)ft_strlen(data->game->map.grid[y]))
		return (true);
	if (data->game->map.grid[y][x] == '1')
		return (true);
	return (false);
}

void	raycasting(t_ray *ray, float angle, t_data *data)
{
	ray->prev_x = ray->ray_x;
	ray->prev_y = ray->ray_y;
	while (!touch_obs(ray->ray_x, ray->ray_y, data))
	{
		ray->prev_x = ray->ray_x;
		ray->prev_y = ray->ray_y;
		ray->ray_x += cos(angle);
		ray->ray_y += sin(angle);
		if (TWO_D)
			put_pixel(ray->ray_x, ray->ray_y, 0xFF0000, data);
		if (ray->ray_x < 0 || ray->ray_x >= data->game->map.width * BLOCK
			|| ray->ray_y < 0 || ray->ray_y >= data->game->map.height * BLOCK)
			break ;
	}
}

void	init_ray(t_ray *ray, t_player *player, float angle)
{
	ray->ray_x = player->x;
	ray->ray_y = player->y;
	ray->ray_dir_x = cos(angle);
	ray->ray_dir_y = sin(angle);
}

void	draw_line(t_player *player, float angle, int i, t_data *data)
{
	t_ray	ray;

	init_ray(&ray, player, angle);
	raycasting(&ray, angle, data);
	if (!TWO_D)
	{
		calc_whntx(&ray, player, angle, data);
		draw_ceiling(&ray, i, data);
		draw_wall(&ray, i, data);
		draw_floor(&ray, i, data);
	}
}

int	raycaster_loop(t_data *data)
{
	int		i;
	float	start_x;
	float	step;

	move_player(&data->player, data);
	clear_image(data);
	if (TWO_D)
	{
		draw_square(data->player.x, data->player.y, 10, data);
		draw_map(data);
	}
	step = (float)(FOV * PI / 180.0) / WIDTH;
	start_x = data->player.angle - (FOV * PI / 180.0) / 2;
	i = -1;
	while (++i < WIDTH)
	{
		draw_line(&data->player, start_x, i, data);
		start_x += step;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
