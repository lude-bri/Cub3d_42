/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:47:22 by mde-agui          #+#    #+#             */
/*   Updated: 2025/01/30 18:58:38 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (perror("Error\nHint: ./cub3D <map.cub>\n"), 1);
	// Initialize all data to 0
	ft_memset(&data, 0, sizeof(t_data));
	// Parse map file
	if (!parser(argv[1], &data.game))
		return (perror("Error\nFailure to parse map file\n"), 1);
	// Initialize window and MLX
	if (!init_window(&data))
		return (perror("Error\nFailure to initialize window\n"), 1); //free before returning if needed
	// Initialize player position and direction
	init_player(&data.player, &data.game);
	// Set up hooks
	// Main game loop (raycasting here?)
	return (0);
}