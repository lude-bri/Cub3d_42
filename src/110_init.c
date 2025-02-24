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

void	init_struct(t_data *data)
{
	t_game	game;

	ft_memset(data, 0, sizeof(t_data));
	ft_memset(&game, 0, sizeof(t_game));
	data->game = &game;
}
