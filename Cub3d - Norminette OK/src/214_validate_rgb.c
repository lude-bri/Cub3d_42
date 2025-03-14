/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   214_validate_rgb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:13:26 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 17:14:01 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	validate_rgb(t_game *game)
{
	if (game->floor.r == -1 || game->floor.g == -1 || game->floor.b == -1
		|| game->ceiling.r == -1 || game->ceiling.g == -1
		|| game->ceiling.b == -1)
		return (FAILURE);
	if (ft_isdigit(game->floor.r) && ft_isdigit(game->floor.g)
		&& ft_isdigit(game->floor.b) && ft_isdigit(game->ceiling.r)
		&& ft_isdigit(game->ceiling.g) && ft_isdigit(game->ceiling.b))
		return (FAILURE);
	if (!out_of_range(game))
		return (FAILURE);
	game->floor.hex = convert_rgb_to_hex(&game->floor);
	game->ceiling.hex = convert_rgb_to_hex(&game->ceiling);
	return (SUCCESS);
}
