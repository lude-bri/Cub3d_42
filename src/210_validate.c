/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-bri <lude-bri@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:27:45 by luigi             #+#    #+#             */
/*   Updated: 2025/03/05 11:56:21 by lude-bri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static unsigned long	convert_rgb_to_hex(t_color *color)
{
	unsigned long	hex;

	hex = ((color->r & 0xff) << 16) + ((color->g & 0xff) << 8) + (color->b & 0xff);
	return (hex);
}

int	validate_textures(t_game *game)
{
	if (!game->north.path || !game->south.path || !game->west.path
		|| !game->east.path)
		return (FAILURE);
	if (check_texture(game->north.path) == FAILURE
		|| check_texture(game->south.path) == FAILURE
		|| check_texture(game->west.path) == FAILURE
		|| check_texture(game->east.path) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

int	validate_rgb(t_game *game)
{
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

int	validate_map(t_map *map)
{
	(void)map;
	return (SUCCESS);
}

int	_validate_data(t_game **game)
{
	//validar se as texturas existem
	if (!validate_textures(*game))
		error(TEXTURE);

	//validar se os rgb estao corretos
	if (!validate_rgb(*game))
		error(RGB);
	
	//validar se o mapa esta correto
	if (!validate_map(&(*game)->map))
		error(MAP);
	return (SUCCESS);
}
