/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:00:58 by mde-agui          #+#    #+#             */
/*   Updated: 2025/02/27 23:53:08 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	is_map(t_game *game)
{
	if (game->count >= 8 && game->south.path && game->north.path
		&& game->east.path && game->west.path)
		return (true);
	return (false);
}

//verify if it is .cub
int	sanity_check(char *file, char *type)
{
	int		len;

	len = ft_strlen(file);
	if (len > 4 && ft_strcmp(file + len - 4, type) == 0)
		return (SUCCESS);
	return (FAILURE);
}

int	init_game_struct(char *line, t_game *game, t_data *data)
{
	if (!line || !*line)
		return (FAILURE);
	while (is_whitespace(*line))
		line++;
	if (*line == 'N' || *line == 'W' || *line == 'S' || *line == 'E')
		set_coord(line, game, data);
	else if (*line == 'F' || *line == 'C')
		set_fc(line, game, data);
	else if (is_map(game) == true) //8 is the minimum of a correct map
		if (!set_map(line, &game->map, data))
			return (FAILURE);
	return (SUCCESS);
}

int	_parser(char *file, t_data *data, t_game *game)
{
	int		fd;
	char	*line;

	if (!sanity_check(file, ".cub"))
		return (FAILURE);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if(!init_game_struct(line, game, data))
			return (FAILURE);
		free(line);
		line = get_next_line(fd);
		game->count++;
	}
	return (SUCCESS);
}
