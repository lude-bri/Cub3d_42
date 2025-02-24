/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:00:58 by mde-agui          #+#    #+#             */
/*   Updated: 2025/02/13 16:30:50 by luigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	sanity_check(char *file)
{
	int		len;

	len = ft_strlen(file);
	if (len > 4 && ft_strcmp(file + len - 4, ".cub") == 0)
		return (SUCCESS);
	return (FAILURE);
}

static int	is_whitespace(char line)
{
	return ((line == ' ') || (line == '\t'));
}

static void	assign_path(char *line, char *id, char **target)
{
	if (line[0] == id[0] && line[1] == id[1])
	{
		line += 3;
		*target = ft_strdup(line);
	}
}

static void	set_coord(char *line, t_game *game)
{
	assign_path(line, "NO", &game->north.path);
	assign_path(line, "SO", &game->south.path);
	assign_path(line, "WE", &game->west.path);
	assign_path(line, "EA", &game->east.path);
}

static void	set_fc(char *line, t_game *game)
{
	(void)line;
	(void)game;
}

static int	init_game_struct(char *line, t_game *game)
{
	if (!line || !*line)
		return (FAILURE);
	while (is_whitespace(*line))
		line++;
	if (*line == 'N' || *line == 'W' || *line == 'S' || *line == 'E')
		set_coord(line, game);
	else if (*line == 'F' || *line == 'C')
		set_fc(line, game);
	return (SUCCESS);
}

int	_parser(char *file, t_game *game)
{
	int		fd;
	char	*line;

	//verify if is .cub
	if (!sanity_check(file))
		return (FAILURE);
	//init
	// ft_memset(&game, 0, sizeof(t_game));
	//open and read
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if(!init_game_struct(line, game))
			return (FAILURE);
		// printf("line -> %s", line);
		line = get_next_line(fd);
	}
	return (SUCCESS);
}
//
// // Function to check if line starts with identifier
// int	is_identifier(char *line, char *id)
// {
// 	while (*line && *line == ' ')
// 		line++;
// 	while (*id)
// 	{
// 		if (*line != *id)
// 			return (0);
// 		line++;
// 		id++;
// 	}
// 	return (1);
// }
//
// // Main parsing function
// int	parse_file(char *filename, t_game *game)
// {
// 	int		fd;
// 	char	*line;
//
// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	// Initialize game structure
// 	ft_memset(game, 0, sizeof(t_game));
// 	// Read file line by line
// 	line = get_next_line(&fd);
// 	while (line && *line)
// 	{
// 		if (is_identifier(*line, "NO"))
// 			parse_texture(*line, &game->north.path);
// 		else if (is_identifier(*line, "SO"))
// 			parse_texture(*line, &game->south.path);
// 		else if (is_identifier(*line, "WE"))
// 			parse_texture(*line, &game->west.path);
// 		else if (is_identifier(*line, "EA"))
// 			parse_texture(*line, &game->east.path);
// 		else if (is_identifier(*line, "F"))
// 			parse_color(*line, &game->floor);
// 		else if (is_identifier(line, "C"))
// 			parse_color(*line, &game->ceiling);
// 		free(*line);
// 		free(line);
// 		line = get_next_line(&fd);
// 	}
// 	close(fd);
// 	return (1);
// }
