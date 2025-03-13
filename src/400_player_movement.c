/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   400_player_movement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:54:46 by luigi             #+#    #+#             */
/*   Updated: 2025/03/12 22:12:25 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	game_exit(t_data *data)
{
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
}

void	init_player(t_player *player, t_map *map)
{
	player->x = (map->player_x + 0.5) * BLOCK;
	player->y = (map->player_y + 0.5) * BLOCK;
	if (map->player_dir == 'N')
		player->angle = 3 * PI / 2;
	else if (map->player_dir == 'S')
		player->angle = PI / 2;
	else if (map->player_dir == 'W')
		player->angle = PI;
	else if (map->player_dir == 'E')
		player->angle = 0;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -sin(player->angle) * 0.66;
	player->plane_y = cos(player->angle) * 0.66;
	player->key_w = false;
	player->key_s = false;
	player->key_a = false;
	player->key_d = false;
	player->key_left = false;
	player->key_right = false;
	player->key_shift = false;
	player->key_esc = false;
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
	else if (keysim == XK_Shift_L)
		player->key_shift = true;
	else if (keysim == XK_Escape)
		player->key_esc = true;
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
	else if (keysim == XK_Shift_L)
		player->key_shift = false;
	else if (keysim == XK_Escape)
		player->key_esc = true;
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

void	move_player(t_player *player, t_data *data)
{
	float	move_speed;
	float	cos_angle;
	float	sin_angle;
	float	new_x;
	float	new_y;

	move_speed = 10;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	rotate_player(player, ROTATE_SPEED);
	//move_player_position(player, move_speed, cos_angle, sin_angle);
	if (player->key_shift)
		move_speed *= 4;
	if (player->key_w)
	{
		new_x = player->x + cos_angle * move_speed;
		new_y = player->y + sin_angle * move_speed;
		if (!touch_obs(new_x, player->y, data))
			player->x = new_x;
		if (!touch_obs(player->x, new_y, data))
			player->y = new_y;
	}
	else if (player->key_s)
	{
		new_x = player->x - cos_angle * move_speed;
		new_y = player->y - sin_angle * move_speed;
		if (!touch_obs(new_x, player->y, data))
			player->x = new_x;
		if (!touch_obs(player->x, new_y, data))
			player->y = new_y;
	}
	else if (player->key_a)
	{
		new_x = player->x + sin_angle * move_speed;
		new_y = player->y - cos_angle * move_speed;
		if (!touch_obs(new_x, player->y, data))
			player->x = new_x;
		if (!touch_obs(player->x, new_y, data))
			player->y = new_y;
	}
	else if (player->key_d)
	{
		new_x = player->x - sin_angle * move_speed;
		new_y = player->y + cos_angle * move_speed;
		if (!touch_obs(new_x, player->y, data))
			player->x = new_x;
		if (!touch_obs(player->x, new_y, data))
			player->y = new_y;
	}
	else if (player->key_esc)
		game_exit(data);
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -sin(player->angle) * 0.66;
	player->plane_y = cos(player->angle) * 0.66;
}

// Implement arrow keys (left and right) for looking
