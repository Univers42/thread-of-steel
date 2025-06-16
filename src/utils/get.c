/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:51:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:24:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_white_color(t_point p1, t_point p2, t_data *data)
{
	(void)p1;
	(void)p2;
	(void)data;
	return (0xFFFFFF);
}

static int	get_gradient_color(t_point p1, t_point p2, t_data *data)
{
	int	avg_z;
	int	z_range;
	int	ratio_256;

	avg_z = (p1.z + p2.z) >> 1;
	z_range = data->map->max_z - data->map->min_z;
	if (z_range == 0)
		return (0xFFFFFF);
	ratio_256 = ((avg_z - data->map->min_z) << 8) / z_range;
	if (ratio_256 < 128)
		return (ratio_256 << 1) << 8;
	else
		return (0xFF0000 | (((255 - ratio_256) << 1) << 8));
}

static int	get_rainbow_color(t_point p1, t_point p2, t_data *data)
{
	static int	hue = 0;

	(void)p1;
	(void)p2;
	(void)data;
	hue = (hue + 1) & 0x167;
	return (0xFF0000 | (hue << 8) | ((360 - hue) << 16));
}

int	get_color(t_point p1, t_point p2, t_data *data)
{
	if (data->controls->color_theme > 0)
	{
		int avg_z = (p1.z + p2.z) >> 1;
		return (get_themed_color(avg_z, data->map->min_z, data->map->max_z,
				data->controls->color_theme));
	}
	static int	(*color_functions[4])(t_point, t_point, t_data*) = {
		get_white_color,
		get_gradient_color,
		get_rainbow_color,
		get_white_color
	};
	return (color_functions[data->controls->color_mode & 0x03](p1, p2, data));
}




