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

static int	verify_player(t_map *map, char c, int *player_count)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map->player_dir = c;
		player_count++;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	validate_rows(t_map *map, int y)
{
	int	x;
	int	player_count;

	player_count = 0;
	
	//fim da grid
	if (y >= map->height)
		return (FAILURE);
	if (map->grid[y] == NULL)
		return (FAILURE);
	
	//verificar largura, possible characters(6) e existencia de player
	while (map->grid[y])
	{
		x = -1;
		while (map->grid[y][++x] != '\n')
		{
			if (map->grid[y][x] != ' ' && map->grid[y][x] != '0'
				&& map->grid[y][x] != '1' && map->grid[y][x] != '\n')
			{
				if (!verify_player(map, map->grid[y][x], &player_count))
					return (FAILURE);
				else
				{
					map->player_x = x;
					map->player_y = y;
				}
			}
		}
		y++;
	}
	if (player_count != 1)
		error(PLAYER);
	return (SUCCESS);
}

//set coord
static int	set_map_coord(t_map *map)
{
	int		x;
	int		y;
	int		max_width;

	y = 0;
	if (!map->grid)
		return (FAILURE);
	while (map->grid[y])
		y++;
	map->height = y;
	y = 0;
	max_width = 0;
	while (map->grid[y])
	{
		x = 0;
		if (map->grid[y][x] == '\t')
			error(MAP);
		while (map->grid[y][x] != '\n')
			x++;
		if (max_width == 0)
			max_width = x;
		if (max_width > x)
			map->width = max_width;
		y++;
	}
	return (SUCCESS);
}

int	validate_map(t_map *map)
{
	//ver se mapa existe
	if (!set_map_coord(map))
		return (FAILURE);
	if (map->width <= 0 || map->height <= 0 || map->grid == NULL)
		return (FAILURE);
	//validar caracteres e verificar se o jogador existe
	if (!validate_rows(map, 0))
		return (FAILURE);
	//Varificar se o mapa esta rodeado de paredes, neste caso em cima e baixo (flood_fill)
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
