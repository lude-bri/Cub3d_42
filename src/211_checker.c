/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   211_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lude-bri <lude-bri@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:31:30 by lude-bri          #+#    #+#             */
/*   Updated: 2025/03/05 11:01:59 by lude-bri         ###   ########.fr       */
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

int	check_texture(char *path)
{
	int		fd;
	char	*new_path;

	new_path = ft_strtrim(path, "\n");
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
