/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:44:23 by mde-agui          #+#    #+#             */
/*   Updated: 2025/02/25 15:52:46 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "../lib/mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include "../lib/libft/libft_42/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define WIDTH 1280
# define HEIGHT 720
# define FOV 60
# define BLOCK 64
# define MOVE_SPEED 2
# define ROTATE_SPEED 0.5
# define PI 3.14159265359
# define TWO_D 0 

//reminder of player coord when spawn
//NORTH -> PI / 2
//SOUTH -> 3 * PI / 2
//WEST -> PI
//EAST -> PI * 2

/* ************************************************************************** */
/*                                  ENUMS								  	  */
/* ************************************************************************** */

//Cub3D Status
typedef enum e_status
{
	FAILURE,
	SUCCESS
}	t_status;

//Error Handlers
typedef enum e_error
{
	PARSE,
	ARG,
	INIT_GAME,
	INIT_WINDOW,
}	t_error;

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_game		t_game;
typedef struct s_map		t_map;

//image struct
typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}			t_img;

//player struct -> coord
typedef struct s_player
{
    float  x;
    float  y;
    float   angle;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
	bool         key_w;
    bool         key_s;
    bool         key_a;
    bool         key_d;
    bool         key_left;
    bool         key_right;
}			t_player;

//keys + events struct
typedef struct s_data
{
    void		*mlx;
    void		*win;
    void		*wall_t;
    t_img		img;
    t_game      *game;
    t_map       *map;
    t_player    player;
	char		*data;
}				t_data;

//texture struct
typedef struct s_texture
{
    char    *path;
    void    *img;
    int     width;
    int     height;
}			t_texture;

//colour struct
typedef struct s_color
{
    int r;
    int g;
    int b;
}		t_color;

//map struct
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    char    player_dir;  // N, S, E, or W
    int     player_x;
    int     player_y;
}			t_map;

//game struct
typedef struct s_game
{
	int			count;
    t_texture   north;
    t_texture   south;
    t_texture   west;
    t_texture   east;
    t_color     floor;
    t_color     ceiling;
    t_map       map;
}				t_game;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// Function prototypes

//110 - INIT
void	init_struct(t_data **data);

//200 - PARSE


//int     init_game(t_data *data, char *map_path);
int     init_mlx(t_data *data);
int     parse_file(char *filename, t_game *game);
int     handle_keypress(int keycode, t_data *data);
int     handle_keyrelease(int keycode, t_data *data);
int     handle_exit(t_data *data);
void    raycasting(t_data *data);
int		_parser(char *file, t_game *game);

void	init_player(t_player *player);
int		key_press(int keysim, t_player *player);
int		key_release(int keysim, t_player *player);
void	rotate_player(t_player *player, float angle_speed);
void	move_player_position(t_player *player, int speed, float cos_angle, float sin_angle);
void	move_player(t_player *player);

int	draw_loop(t_data *data);

//900 - ERROR HANDLERS
void	error(int	no);

#endif
