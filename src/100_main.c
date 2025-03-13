/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:47:22 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/12 23:48:39 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_game(t_data *data)
{
	/* int	width;
	int	height; */
	
	init_player(&data->player, &data->game->map);
	data->map = &data->game->map;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, 
								&data->img.line_length, &data->img.endian);
	data->data = data->img.addr;
	data->game->north.img = mlx_xpm_file_to_image(data->mlx, data->game->north.path, &data->game->north.width, &data->game->north.height);
	data->game->south.img = mlx_xpm_file_to_image(data->mlx, data->game->south.path, &data->game->south.width, &data->game->south.height);
	data->game->east.img = mlx_xpm_file_to_image(data->mlx, data->game->east.path, &data->game->east.width, &data->game->east.height);
	data->game->west.img = mlx_xpm_file_to_image(data->mlx, data->game->west.path, &data->game->west.width, &data->game->west.height);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		//init structs
		init_struct(&data);

		//parse everything
		if (!_parser(av[1], data, data->game))
			error(PARSE, data);

		//validate data
		if (!_validate_data(&data->game, data))
			error(VALIDATE, data);
		
		init_game(data);
		//send the parsed map to mlx loop
		mlx_hook(data->win, 2, 1L<<0, key_press, &data->player);
		mlx_hook(data->win, 3, 1L<<1, key_release, &data->player);
		mlx_hook(data->win, 17, 1L<<17, game_exit, data);
		mlx_loop_hook(data->mlx, draw_loop, data);
		mlx_loop(data->mlx);
		return (0);
	}
	else
		error(ARG, 0);
}
