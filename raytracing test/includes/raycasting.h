#ifndef RAYCASTING_H
#define RAYCASTING_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define PI	3.14159265359

// # include "../minilibx-linux/mlx.h"
# include "../lib/mlx/mlx.h"
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;

	char		**map;
	char		*data;
	int			bpp;
	int			line_size;
	int			endian;
	t_player	player;
}				t_game;

void	init_player(t_player *player);
int		key_press(int keysim, t_player *player);
int		key_release(int keysim, t_player *player);
void	move_player(t_player *player);
int		draw_loop(t_game *game);
void	init_game(t_game *game);


#endif
