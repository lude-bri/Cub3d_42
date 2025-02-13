/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:00:58 by mde-agui          #+#    #+#             */
/*   Updated: 2025/01/30 19:04:11 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Function to check if line starts with identifier
int	is_identifier(char *line, char *id)
{
	while (*line && *line == ' ')
		line++;
	while (*id)
	{
		if (*line != *id)
			return (0);
		line++;
		id++;
	}
	return (1);
}

// Main parsing function
int	parse_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	// Initialize game structure
	ft_memset(game, 0, sizeof(t_game));
	// Read file line by line
	line = get_next_line(&fd);
	while (line && *line)
	{
		if (is_identifier(*line, "NO"))
			parse_texture(*line, &game->north.path);
		else if (is_identifier(*line, "SO"))
			parse_texture(*line, &game->south.path);
		else if (is_identifier(*line, "WE"))
			parse_texture(*line, &game->west.path);
		else if (is_identifier(*line, "EA"))
			parse_texture(*line, &game->east.path);
		else if (is_identifier(*line, "F"))
			parse_color(*line, &game->floor);
		else if (is_identifier(line, "C"))
			parse_color(*line, &game->ceiling);
		free(*line);
		free(line);
		line = get_next_line(&fd);
	}
	close(fd);
	return (1);
}
