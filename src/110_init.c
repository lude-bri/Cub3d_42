/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   110_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-bri <lude-bri@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:36:24 by luigi             #+#    #+#             */
/*   Updated: 2025/02/24 11:39:33 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_values(t_data *data)
{
	data->game->north.path = NULL;
	data->game->south.path = NULL;
	data->game->east.path = NULL;
	data->game->west.path = NULL;
	data->game->floor.r = -1;
	data->game->floor.g = -1;
	data->game->floor.b = -1;
	data->game->ceiling.r = -1;
	data->game->ceiling.g = -1;
	data->game->ceiling.b = -1;
}

void	init_struct(t_data **data)
{
	*data = malloc(sizeof(t_data));
	ft_memset(*data, 0, sizeof(t_data));
	(*data)->game = malloc(sizeof(t_game));
	ft_memset((*data)->game, 0, sizeof(t_game));
	init_values(*data);
	(*data)->game->map.grid = NULL;
}
