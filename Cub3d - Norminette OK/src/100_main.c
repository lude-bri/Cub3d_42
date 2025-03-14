/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:47:22 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 18:35:12 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		init_struct(&data);
		if (!_parser(av[1], data, data->game))
			error(PARSE, data);
		if (!_validate_data(&data->game, data))
			error(VALIDATE, data);
		init_game(data);
		mlx_hook(data->win, 2, 1L << 0, key_press, &data->player);
		mlx_hook(data->win, 3, 1L << 1, key_release, &data->player);
		mlx_hook(data->win, 17, 1L << 17, game_exit, data);
		mlx_loop_hook(data->mlx, raycaster_loop, data);
		mlx_loop(data->mlx);
		return (0);
	}
	else
		error(ARG, 0);
}
