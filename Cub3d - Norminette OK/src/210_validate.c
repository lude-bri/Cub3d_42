/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:27:45 by luigi             #+#    #+#             */
/*   Updated: 2025/03/14 18:31:11 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	verify_player(t_map *map, char c, int player_count)
{
	(void)player_count;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->player_dir = c;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	_validate_data(t_game **game, t_data *data)
{
	if (!validate_textures(*game))
		error(TEXTURE, data);
	if (!validate_rgb(*game))
		error(RGB, data);
	if (!validate_map((&(*game)->map), data))
		error(MAP, data);
	return (SUCCESS);
}
