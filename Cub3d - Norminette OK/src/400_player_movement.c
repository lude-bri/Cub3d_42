/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_player_movement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:54:46 by luigi             #+#    #+#             */
/*   Updated: 2025/03/14 18:44:54 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	update_direction_vectors(t_player *player)
{
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -sin(player->angle) * 0.66;
	player->plane_y = cos(player->angle) * 0.66;
}

void	rotate_player(t_player *player, float angle_speed)
{
	if (player->key_left)
		player->angle -= angle_speed;
	if (player->key_right)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	move_player(t_player *player, t_data *data)
{
	float	move_speed;

	move_speed = 10;
	rotate_player(player, ROTATE_SPEED);
	if (player->key_shift)
		move_speed *= 2;
	if (player->key_w)
		move_forward(player, data, move_speed);
	else if (player->key_s)
		move_backward(player, data, move_speed);
	else if (player->key_a)
		move_left(player, data, move_speed);
	else if (player->key_d)
		move_right(player, data, move_speed);
	else if (player->key_esc)
		game_exit(data);
	update_direction_vectors(player);
}
