/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:47:22 by mde-agui          #+#    #+#             */
/*   Updated: 2025/01/30 18:52:27 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void init_player(t_player *player, t_game *game)
{
    // Set initial position based on map
    player->x = game->map.player_x + 0.5;
    player->y = game->map.player_y + 0.5;
    
    // Set initial direction based on spawn orientation
    if (game->map.player_dir == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    // Add other directions (S, E, W) similarly
}

static int init_window(t_data *data)
{
    data->mlx.mlx = mlx_init();
    if (!data->mlx.mlx)
        return (0);
    
    data->mlx.win = mlx_new_window(data->mlx.mlx, WINDOW_WIDTH, 
                                  WINDOW_HEIGHT, "cub3D");
    if (!data->mlx.win)
        return (0);
    
    data->mlx.img.img = mlx_new_image(data->mlx.mlx, WINDOW_WIDTH, 
                                     WINDOW_HEIGHT);
    if (!data->mlx.img.img)
        return (0);
    
    data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img, 
                                          &data->mlx.img.bits_per_pixel,
                                          &data->mlx.img.line_length,
                                          &data->mlx.img.endian);
    return (1);
}

int main(int argc, char **argv)
{
    t_data  data;

    if (argc != 2)
        return (perror("Error\nHint: ./cub3D <map.cub>\n"), 1);
    // Initialize all data to 0
    ft_memset(&data, 0, sizeof(t_data));
    // Parse map file
    if (!parser(argv[1], &data.game))
        return (perror("Error\nFailure to parse map file\n"), 1);
    // Initialize window and MLX
    if (!init_window(&data))
        return (perror("Error\nFailure to initialize window\n"), 1); //free before returning if needed
    // Initialize player position and direction
    init_player(&data.player, &data.game);
    // Set up hooks
    mlx_hook(data.mlx.win, 2, 1L<<0, handle_keypress, &data);
    mlx_hook(data.mlx.win, 3, 1L<<1, handle_keyrelease, &data);
    mlx_hook(data.mlx.win, 17, 0, handle_exit, &data);
    // Main game loop (raycasting here?)
    mlx_loop_hook(data.mlx.mlx, (void *)raycasting, &data);
    mlx_loop(data.mlx.mlx);
    return (0);
}