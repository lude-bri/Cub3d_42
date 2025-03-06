/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-bri <lude-bri@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:27:45 by luigi             #+#    #+#             */
/*   Updated: 2025/03/05 12:33:27 by lude-bri         ###   ########.fr       */
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

int	validate_rows(t_map *map, int y, int *player_count)
{
	int	x;

	x = 0;
	//fim da grid
	if (y >= HEIGHT)
		return (FAILURE);
	if (map->grid[y] == NULL)
		return (FAILURE);
	//verificar largura
	while (map->grid[y][x] != '\0')
		x++;
	if (x != WIDTH)
		return (FAILURE)
}

int	validate_map(t_map *map)
{
	int	player_count;

	player_count = 0;
	//ver se mapa existe
	if (WIDTH <= 0 || HEIGHT <= 0 || map->grid == NULL)
		return (FAILURE);
	//validar caracteres e verificar se o jogador existe
	if (!validate_rows(map, 0, &player_count))
		return (FAILURE);
	//Verificar se um e so um jogador existe
	if (player_count != 1)
		return (FAILURE);
	//Varificar se o mapa esta rodeado de paredes, neste caso em cima e baixo
	if (!check_edge(map, map->grid[0], 0) || !check_edge(map, map->grid[HEIGHT - 1], 0))
		return (FAILURE);
	//o mesmo, so que os lados
	if (!check_sides(map, 0, 0) || !check_sides(map, 0, WIDTH - 1))
		return (FAILURE);
	//validar se esta rodeado por paredes
	//a primeira e a ultima linha necessariamente tem que ser composta por 1 ou espacos
	//o primeiro caracter 
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
