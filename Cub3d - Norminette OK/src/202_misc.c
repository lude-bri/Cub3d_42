/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   202_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-agui <mde-agui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:16:02 by mde-agui          #+#    #+#             */
/*   Updated: 2025/03/14 17:33:58 by mde-agui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_whitespace(char line)
{
	return ((line == ' ') || (line == '\t'));
}

unsigned long	convert_rgb_to_hex(t_color *color)
{
	unsigned long	hex;

	hex = ((color->r & 0xFF) << 16) + ((color->g & 0xFF) << 8)
		+ (color->b & 0xFF);
	return (hex);
}

void	clear_image(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			put_pixel(x, y, 0, data);
	}
}

void	put_pixel(int x, int y, unsigned int color, t_data *data)
{
	int	i;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y <= 0)
		return ;
	i = y * data->img.line_length + x * data->img.bits_per_pixel / 8;
	data->data[i] = color & 0xFF;
	data->data[i + 1] = (color >> 8) & 0xFF;
	data->data[i + 2] = (color >> 16) & 0xFF;
}
