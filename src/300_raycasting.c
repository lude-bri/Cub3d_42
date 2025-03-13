/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_raycasting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:24:19 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/13 16:22:44 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(int x, int y, unsigned int color, t_data *data)
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

	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	if (y < 0 || y >= data->game->map.height || x < 0 ||
		x >= (int)ft_strlen(data->game->map.grid[y]))
		return (true);
	if (data->game->map.grid[y][x] == '1')
		return (true);
	return (false);
}

void	calc_dist_and_angle(t_ray *ray, t_player *player, float angle)
{
	ray->dist = sqrt((ray->ray_x - player->x) * (ray->ray_x - player->x) + (ray->ray_y - player->y) * (ray->ray_y - player->y));
	ray->angle_dif = player->angle - angle;
	if (ray->angle_dif < 0)
		ray->angle_dif += 2 * PI;
	if (ray->angle_dif > 2 * PI)
		ray->angle_dif -= 2 * PI;
	ray->dist *= cos(ray->angle_dif);
}

void	calc_wall_h_and_draw_range(t_ray *ray)
{
	ray->height = (int)((BLOCK / ray->dist) * (HEIGHT / tan(PI / 6)));

	ray->draw_start = -ray->height / 2 + HEIGHT / 2;
	ray->draw_end = ray->height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0) ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT) ray->draw_end = HEIGHT - 1;
}

void	determine_wall_dir(t_ray *ray)
{
	if (ray->prev_map_y != ray->map_y)
	{
		if (ray->prev_y < ray->ray_y)
			ray->wall_dir = 1; // South
		else
			ray->wall_dir = 0; // North
	}
	else if (ray->prev_map_x != ray->map_x)
	{
		if (ray->prev_x < ray->ray_x)
			ray->wall_dir = 2; // East
		else
			ray->wall_dir = 3; // West
	}
}

void	select_texture(t_ray *ray, t_data *data)
{
	if (ray->wall_dir == 0) // North
	{
		ray->tx_img = data->game->north.img;
		ray->wall_x = ray->ray_x / BLOCK - (int)(ray->ray_x / BLOCK);
	}
	else if (ray->wall_dir == 1) // South
	{
		ray->tx_img = data->game->south.img;
		ray->wall_x = ray->ray_x / BLOCK - (int)(ray->ray_x / BLOCK);
	}
	else if (ray->wall_dir == 2) // East
	{
		ray->tx_img = data->game->east.img;
		ray->wall_x = ray->ray_y / BLOCK - (int)(ray->ray_y / BLOCK);
	}
	else if (ray->wall_dir == 3) // West
	{
		ray->tx_img = data->game->west.img;
		ray->wall_x = ray->ray_y / BLOCK - (int)(ray->ray_y / BLOCK);
	}
}

void	determine_wall_hit_and_tx(t_ray *ray, t_data *data)
{
	ray->prev_map_y = (int)(ray->prev_y / BLOCK);
	ray->map_y = (int)(ray->ray_y / BLOCK);
	ray->prev_map_x = (int)(ray->prev_x / BLOCK);
	ray->map_x = (int)(ray->ray_x / BLOCK);

	determine_wall_dir(ray);
	select_texture(ray, data);
}

void	correct_tx_coord(t_ray *ray)
{
	ray->tx_x = (int)(ray->wall_x * 64);
	if (ray->wall_dir == 0 && ray->ray_dir_y > 0)
		ray->tx_x = 64 - ray->tx_x - 1;
	else if (ray->wall_dir == 1 && ray->ray_dir_y > 0)
		ray->tx_x = 64 - ray->tx_x - 1;
	else if (ray->wall_dir == 2 && ray->ray_dir_x < 0)
		ray->tx_x = 64 - ray->tx_x - 1;
	else if (ray->wall_dir == 3 && ray->ray_dir_x > 0)
		ray->tx_x = 64 - ray->tx_x - 1;
	if (ray->tx_x < 0)
		ray->tx_x = 0;
	if (ray->tx_x >= 64)
		ray->tx_x = 63;
	ray->tx_addr = mlx_get_data_addr(ray->tx_img, &ray->tx_bpp, &ray->tx_l, &ray->tx_endian);
}

void	draw_floor(t_ray *ray, int i, t_data *data)
{
	while (ray->y < HEIGHT)
		put_pixel(i, ray->y++, data->game->floor.hex, data);
}

void	draw_wall(t_ray *ray, int i, t_data *data)
{
	ray->tex_height = 64;
	ray->step = ray->tex_height / (float)ray->height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->height / 2) * ray->step;
	ray->y = ray->draw_start;
	while (ray->y < ray->draw_end && ray->y < HEIGHT)
	{
		ray->tx_y = ray->tex_pos;
		if (ray->tx_y >= ray->tex_height)
			ray->tx_y = ray->tex_height - 1;
		ray->txpp = (int)ray->tx_y * ray->tx_l + ray->tx_x * (ray->tx_bpp / 8);
		ray->b = ray->tx_addr[ray->txpp];
		ray->g = ray->tx_addr[ray->txpp + 1];
		ray->r = ray->tx_addr[ray->txpp + 2];
		ray->color = (ray->r << 16) | (ray->g << 8) | ray->b;
		ray->shade_factor = 1.0;
		if (ray->dist > BLOCK)
			ray->shade_factor = BLOCK / ray->dist;
		if (ray->shade_factor < 0.3)
			ray->shade_factor = 0.3;
		ray->shade_r = (int)(ray->r * ray->shade_factor);
		ray->shade_g = (int)(ray->g * ray->shade_factor);
		ray->shade_b = (int)(ray->b * ray->shade_factor);
		ray->color = (ray->shade_r << 16) | (ray->shade_g << 8) | ray->shade_b;
		put_pixel(i, ray->y++, ray->color, data);
		ray->tex_pos += ray->step;
	}
}

void	draw_ceiling(t_ray *ray, int i, t_data *data)
{
	ray->y = 0;
	while (ray->y < ray->draw_start)
		put_pixel(i, ray->y++, data->game->ceiling.hex, data);
}

void	calc_wall_h_and_tx(t_ray *ray, t_player *player, float angle, t_data *data)
{
	calc_dist_and_angle(ray, player, angle);
	calc_wall_h_and_draw_range(ray);
	determine_wall_hit_and_tx(ray, data);
	correct_tx_coord(ray);
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
		if (ray->ray_x < 0 || ray->ray_x >= data->game->map.width * BLOCK ||
			ray->ray_y < 0 || ray->ray_y >= data->game->map.height * BLOCK)
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
		calc_wall_h_and_tx(&ray, player, angle, data);
		draw_ceiling(&ray, i, data);
		draw_wall(&ray, i, data);
		draw_floor(&ray, i, data);
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

	move_player(&data->player, data);
	clear_image(data);
	if (TWO_D)
	{
		draw_square(data->player.x, data->player.y, 10, data);
		draw_map(data);
	}
	step = (float)(FOV * PI / 180.0) / WIDTH; // Convert FOV to radians and divide by screen width
	start_x = data->player.angle - (FOV * PI / 180.0) / 2; // Center the FOV around player angle
	i = -1;
	while (++i < WIDTH)
	{
		draw_line(&data->player, start_x, i, data);
		start_x += step;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

