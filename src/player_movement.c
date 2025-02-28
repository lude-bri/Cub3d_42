/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:37:12 by mde-agui          #+#    #+#             */
/*   Updated: 2025/02/20 14:28:22 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->key_w = false;
	player->key_s = false;
	player->key_a = false;
	player->key_d = false;
	player->key_left = false;
	player->key_right = false;
}

int	key_press(int keysim, t_player *player)
{
	if (keysim == XK_w || keysim == XK_W)
		player->key_w = true;
	else if (keysim == XK_s || keysim == XK_S)
		player->key_s = true;
	else if (keysim == XK_a || keysim == XK_A)
		player->key_a = true;
	else if (keysim == XK_d || keysim == XK_D)
		player->key_d = true;
	else if (keysim == XK_Left)
		player->key_left = true;
	else if (keysim == XK_Right)
		player->key_right = true;
	return (0);
}

int	key_release(int keysim, t_player *player)
{
	if (keysim == XK_w || keysim == XK_W)
		player->key_w = false;
	else if (keysim == XK_s || keysim == XK_S)
		player->key_s = false;
	else if (keysim == XK_a || keysim == XK_A)
		player->key_a = false;
	else if (keysim == XK_d || keysim == XK_D)
		player->key_d = false;
	else if (keysim == XK_Left)
		player->key_left = false;
	else if (keysim == XK_Right)
		player->key_right = false;
	return (0);
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

void	move_player_position(t_player *player, int speed, float cos_angle, float sin_angle)
{
	if (player->key_w)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	else if (player->key_s)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	else if (player->key_a)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	else if (player->key_d)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
}

void	move_player(t_player *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	rotate_player(player, ROTATE_SPEED);
	move_player_position(player, MOVE_SPEED, cos_angle, sin_angle);
}

// Implement arrow keys (left and right) for looking
