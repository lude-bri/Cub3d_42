/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   211_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-bri <lude-bri@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:31:30 by lude-bri          #+#    #+#             */
/*   Updated: 2025/03/05 11:18:04 by lude-bri         ###   ########.fr       */
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

	// path = ft_strtrim(path, "\n");
	new_path = ft_strtrim(path, " ");
	if (!sanity_check(new_path, ".xpm"))
		return (FAILURE);
	if (!check_directory(new_path))
		return (FAILURE);
	fd = open(new_path, O_RDONLY);
	if (fd < 0)
		return (FAILURE);
	close(fd);
	return (SUCCESS);
}
