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

static int	assign_path(char *line, char *id, char **target)
{
	if (line[0] == id[0] && line[1] == id[1])
	{
		line += 2;
		while (is_whitespace(*line))
			line++;
		if (*line)
		{
			*target = ft_strdup(line);
			return (SUCCESS);
		}
		else
			error(PARSE);
	}
	return (FAILURE);
}

static void	set_coord(char *line, t_game *game)
{
	if (assign_path(line, "NO", &game->north.path) == SUCCESS ||
		assign_path(line, "SO", &game->south.path) == SUCCESS ||
		assign_path(line, "WE", &game->west.path) == SUCCESS ||
		assign_path(line, "EA", &game->east.path) == SUCCESS)
	{
		return ;
	}
	else
		error(PARSE);
}

static void	set_fc(char *line, t_game *game)
{
	char	**rgb;
	bool	fc; //floor is true - ceiling is false

	fc = false;
	if (*line == 'F')
		fc = true;
	line++;
	if (!is_whitespace(*line))
		error(PARSE);
	while (is_whitespace(*line))
		line++;
	if (line)
	{
		rgb = ft_split(line, ',');
		if (fc == true)
		{
			game->floor.r = ft_atoi(rgb[0]);
			game->floor.g = ft_atoi(rgb[1]);
			game->floor.b = ft_atoi(rgb[2]);
		}
		else
		{
			game->ceiling.r = ft_atoi(rgb[0]);
			game->ceiling.g = ft_atoi(rgb[1]);
			game->ceiling.b = ft_atoi(rgb[2]);
		}
	}
	else
		error(PARSE);
}

static int	set_map(char *line, t_game *game)
{
	(void)line;
	(void)game;
	return (0);
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
	if (game->count >= 8) //8 is the minimum of a correct map
		if (!set_map(line, game))
			return (FAILURE);
	return (SUCCESS);
}

int	_parser(char *file, t_game *game)
{
	int		fd;
	char	*line;

	//verify if is .cub
	if (!sanity_check(file))
		return (FAILURE);
	//open and read
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if(!init_game_struct(line, game))
			return (FAILURE);
		line = get_next_line(fd);
		game->count++;
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
