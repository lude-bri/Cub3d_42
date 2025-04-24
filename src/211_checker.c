/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   211_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:31:30 by lude-bri          #+#    #+#             */
/*   Updated: 2025/03/14 18:39:32 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_directory(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}

int	out_of_range(t_game *game)
{
	if (game->floor.r < 0 || game->floor.r > 255)
		return (FAILURE);
	if (game->floor.g < 0 || game->floor.g > 255)
		return (FAILURE);
	if (game->floor.b < 0 || game->floor.b > 255)
		return (FAILURE);
	if (game->ceiling.r < 0 || game->ceiling.r > 255)
		return (FAILURE);
	if (game->ceiling.g < 0 || game->ceiling.g > 255)
		return (FAILURE);
	if (game->ceiling.b < 0 || game->ceiling.b > 255)
		return (FAILURE);
	return (SUCCESS);
}

int	check_texture(char *path)
{
	int		fd;
	char	*new_path;

	new_path = ft_strtrim(path, " ");
	if (!sanity_check(new_path, ".xpm"))
		return (free(new_path), FAILURE);
	if (!check_directory(new_path))
		return (free(new_path), FAILURE);
	fd = open(new_path, O_RDONLY);
	if (fd < 0)
		return (free(new_path), FAILURE);
	close(fd);
	free(new_path);
	return (SUCCESS);
}
