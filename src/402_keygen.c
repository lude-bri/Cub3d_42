/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   402_keygen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:54:50 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 17:55:47 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
