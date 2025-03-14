/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   302_rayc_draws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:40:13 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 17:41:33 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
		shader(ray, i, data);
		ray->tex_pos += ray->step;
	}
}

void	draw_ceiling(t_ray *ray, int i, t_data *data)
{
	ray->y = 0;
	while (ray->y < ray->draw_start)
		put_pixel(i, ray->y++, data->game->ceiling.hex, data);
}
