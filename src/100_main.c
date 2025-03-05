/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:47:22 by mde-agui          #+#    #+#             */
/*   Updated: 2025/02/27 23:18:21 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	init_game(t_data *game)
// {
// 	init_player(&game->player);
// 	game->mlx = mlx_init();
// 	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
// 	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	game->data = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
// 	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
// }

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		//init structs
		init_struct(&data);

		//parse everything
		if (!_parser(av[1], data->game))
			error(PARSE);

		//validate data
		if (!_validate_data(data->game))
			error(VALIDATE);

		// init_game(data);
		//send the parsed map to mlx loop
		// mlx_hook(data->win, 2, 1L<<0, key_press, &data->player);
		// mlx_hook(data->win, 3, 1L<<1, key_release, &data->player);
		// mlx_loop_hook(data->mlx, draw_loop, &data);
		// mlx_loop(data->mlx);
		return (0);
		//wait till end and close/free
	}
	else
		error(ARG);
}
