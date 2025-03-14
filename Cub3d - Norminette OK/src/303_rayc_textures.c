/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   303_rayc_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:43:47 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 18:55:21 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	shader(t_ray *ray, int i, t_data *data)
{
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
}

void	determine_wall_dir(t_ray *ray)
{
	if (ray->prev_map_y != ray->map_y)
	{
		if (ray->prev_y < ray->ray_y)
			ray->wall_dir = SOUTH;
		else
			ray->wall_dir = NORTH;
	}
	else if (ray->prev_map_x != ray->map_x)
	{
		if (ray->prev_x < ray->ray_x)
			ray->wall_dir = EAST;
		else
			ray->wall_dir = WEST;
	}
}

void	select_texture(t_ray *ray, t_data *data)
{
	if (ray->wall_dir == NORTH)
	{
		ray->tx_img = data->game->north.img;
		ray->wall_x = ray->ray_x / BLOCK - (int)(ray->ray_x / BLOCK);
	}
	else if (ray->wall_dir == SOUTH)
	{
		ray->tx_img = data->game->south.img;
		ray->wall_x = ray->ray_x / BLOCK - (int)(ray->ray_x / BLOCK);
	}
	else if (ray->wall_dir == EAST)
	{
		ray->tx_img = data->game->east.img;
		ray->wall_x = ray->ray_y / BLOCK - (int)(ray->ray_y / BLOCK);
	}
	else if (ray->wall_dir == WEST)
	{
		ray->tx_img = data->game->west.img;
		ray->wall_x = ray->ray_y / BLOCK - (int)(ray->ray_y / BLOCK);
	}
}
