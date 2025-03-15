/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:04:49 by luigi             #+#    #+#             */
/*   Updated: 2025/03/14 18:42:26 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_game(int no, t_data *data)
{
	int		i;

	if (data->game->map.grid)
	{
		i = 0;
		while (data->game->map.grid[i])
			free(data->game->map.grid[i++]);
		free(data->game->map.grid);
	}
	if (data->game->north.path)
		free(data->game->north.path);
	if (data->game->south.path)
		free(data->game->south.path);
	if (data->game->east.path)
		free(data->game->east.path);
	if (data->game->west.path)
		free(data->game->west.path);
	if (data->game)
		free(data->game);
	free(data);
	exit (no);
}

void	error(int no, t_data *data)
{
	if (no == PARSE)
		ft_putstr_fd("Error: Failure to parse map file\n", 2);
	else if (no == INIT_GAME)
		ft_putstr_fd("Error: Failure to initialize game\n", 2);
	else if (no == INIT_WINDOW)
		ft_putstr_fd("Error: Failure to initialize window\n", 2);
	else if (no == ARG)
		ft_putstr_fd("Error: Try ./cub3D <map.cub>\n", 2);
	else if (no == RGB)
		ft_putstr_fd("Error: Invalid or missing color\n", 2);
	else if (no == MAP)
		ft_putstr_fd("Error: Invalid character on map\n", 2);
	else if (no == PLAYER)
		ft_putstr_fd("Error: More than one or not enough players\n", 2);
	else if (no == TEXTURE)
		ft_putstr_fd("Error: Invalid texture\n", 2);
	free_game(no, data);
}
