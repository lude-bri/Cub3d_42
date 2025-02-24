/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:44:23 by mde-agui          #+#    #+#             */
/*   Updated: 2025/02/24 11:38:35 by luigi            ###   ########.fr       */
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
# include "../lib/libft/libft_42/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define FOV 60
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.1

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

//image struct
typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}			t_img;

//mlx struct
typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_img   img;
}			t_mlx;

//player struct -> coord
typedef struct s_player
{
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}			t_player;

//keys + events struct
typedef struct s_data
{
    t_mlx       mlx;
    t_game      *game;
    t_player    player;
    int         key_w;
    int         key_s;
    int         key_a;
    int         key_d;
    int         key_left;
    int         key_right;
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
void	init_struct(t_data *data);

//200 - PARSE
int     init_game(t_data *data, char *map_path);
int     init_mlx(t_data *data);
int     parse_file(char *filename, t_game *game);
int     handle_keypress(int keycode, t_data *data);
int     handle_keyrelease(int keycode, t_data *data);
int     handle_exit(t_data *data);
void    raycasting(t_data *data);
int		_parser(char *file, t_game *game);

//900 - ERROR HANDLERS
void	error(int	no);

#endif
