/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:51:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 11:01:14 by dlesieur         ###   ########.fr       */
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
	// PRIORITY 1: Check if either point has an embedded color (not default white)
	// Use both points to get the most specific color
	if (p1.color != 0xFFFFFF && p2.color != 0xFFFFFF)
	{
		// If both have colors, blend or choose one (here we choose p1)
		return (p1.color);
	}
	else if (p1.color != 0xFFFFFF)
	{
		return (p1.color);
	}
	else if (p2.color != 0xFFFFFF)
	{
		return (p2.color);
	}
	
	// PRIORITY 2: If using color themes and no embedded colors, apply themes
	if (data->controls->color_theme > 0)
	{
		int avg_z = (p1.z + p2.z) >> 1;
		return (get_themed_color(avg_z, data->map->min_z, data->map->max_z,
				data->controls->color_theme));
	}
	
	// PRIORITY 3: Legacy color modes (default to white when no theme)
	if (data->controls->color_mode == 0)
		return (0xFFFFFF);  // White default
	
	static int	(*color_functions[4])(t_point, t_point, t_data*) = {
		get_white_color,
		get_gradient_color,
		get_rainbow_color,
		get_white_color
	};
	return (color_functions[data->controls->color_mode & 0x03](p1, p2, data));
}




