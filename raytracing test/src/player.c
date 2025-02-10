#include "../includes/raycasting.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keysim, t_player *player)
{
	if (keysim == XK_w || keysim == XK_W)
		player->key_up = true;
	else if (keysim == XK_s || keysim == XK_S)
		player->key_down = true;
	else if (keysim == XK_a || keysim == XK_A)
		player->key_left = true;
	else if (keysim == XK_d || keysim == XK_D)
		player->key_right = true;
	else if (keysim == XK_Left)
		player->left_rotate = true;
	else if (keysim == XK_Right)
		player->right_rotate = true;
	return (0);
}

int	key_release(int keysim, t_player *player)
{
	if (keysim == XK_w || keysim == XK_W)
		player->key_up = false;
	else if (keysim == XK_s || keysim == XK_S)
		player->key_down = false;
	else if (keysim == XK_a || keysim == XK_A)
		player->key_left = false;
	else if (keysim == XK_d || keysim == XK_D)
		player->key_right = false;
	else if (keysim == XK_Left)
		player->left_rotate = false;
	else if (keysim == XK_Right)
		player->right_rotate = false;
	return (0);
}

void	move_player(t_player *player)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	speed = 3;
	angle_speed = 0.1;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up)
	{
		player->x += cos_angle * speed;
		player->y += sin_angle * speed;
	}
	else if (player->key_down)
	{
		player->x -= cos_angle * speed;
		player->y -= sin_angle * speed;
	}
	else if (player->key_left)
	{
		player->x += sin_angle * speed;
		player->y -= cos_angle * speed;
	}
	else if (player->key_right)
	{
		player->x -= sin_angle * speed;
		player->y += cos_angle * speed;
	}
}
