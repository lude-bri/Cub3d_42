/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   401_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:48:29 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 17:54:16 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_right(t_player *player, t_data *data, float move_speed)
{
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	new_x = player->x - sin_angle * move_speed;
	new_y = player->y + cos_angle * move_speed;
	if (!touch_obs(new_x, player->y, data))
		player->x = new_x;
	if (!touch_obs(player->x, new_y, data))
		player->y = new_y;
}

void	move_left(t_player *player, t_data *data, float move_speed)
{
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	new_x = player->x + sin_angle * move_speed;
	new_y = player->y - cos_angle * move_speed;
	if (!touch_obs(new_x, player->y, data))
		player->x = new_x;
	if (!touch_obs(player->x, new_y, data))
		player->y = new_y;
}

void	move_backward(t_player *player, t_data *data, float move_speed)
{
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	new_x = player->x - cos_angle * move_speed;
	new_y = player->y - sin_angle * move_speed;
	if (!touch_obs(new_x, player->y, data))
		player->x = new_x;
	if (!touch_obs(player->x, new_y, data))
		player->y = new_y;
}

void	move_forward(t_player *player, t_data *data, float move_speed)
{
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	new_x = player->x + cos_angle * move_speed;
	new_y = player->y + sin_angle * move_speed;
	if (!touch_obs(new_x, player->y, data))
		player->x = new_x;
	if (!touch_obs(player->x, new_y, data))
		player->y = new_y;
}
