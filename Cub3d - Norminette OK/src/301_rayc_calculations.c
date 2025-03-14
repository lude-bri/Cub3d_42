/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   301_rayc_calculations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:35:46 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 19:24:36 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	texture_coord(t_ray *ray)
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
	ray->tx_addr = mlx_get_data_addr(ray->tx_img, &ray->tx_bpp,
			&ray->tx_l, &ray->tx_endian);
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

void	calc_wall_h_and_draw_range(t_ray *ray)
{
	ray->height = (int)((BLOCK / ray->dist) * (HEIGHT / tan(PI / 6)));
	ray->draw_start = -ray->height / 2 + HEIGHT / 2;
	ray->draw_end = ray->height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	calc_dist_and_angle(t_ray *ray, t_player *player, float angle)
{
	ray->dist = sqrt((ray->ray_x - player->x) * (ray->ray_x - player->x)
			+ (ray->ray_y - player->y) * (ray->ray_y - player->y));
	ray->angle_dif = player->angle - angle;
	if (ray->angle_dif < 0)
		ray->angle_dif += 2 * PI;
	if (ray->angle_dif > 2 * PI)
		ray->angle_dif -= 2 * PI;
	ray->dist *= cos(ray->angle_dif);
}

void	calc_whntx(t_ray *ray, t_player *pl, float angle, t_data *data)
{
	calc_dist_and_angle(ray, pl, angle);
	calc_wall_h_and_draw_range(ray);
	determine_wall_hit_and_tx(ray, data);
	texture_coord(ray);
}
