/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:51:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:15:40 by dlesieur         ###   ########.fr       */
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

static int	get_gradient_color_legacy(t_point p1, t_point p2, t_data *data)
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
	static int	(*color_functions[4])(t_point, t_point, t_data*) = {
		get_white_color,
		get_gradient_color_legacy,
		get_rainbow_color,
		get_white_color
	};

	if (p1.color != 0xFFFFFF && p2.color != 0xFFFFFF)
		return (p1.color);
	else if (p1.color != 0xFFFFFF)
		return (p1.color);
	else if (p2.color != 0xFFFFFF)
		return (p2.color);
	if (data->controls->color_theme > 0)
	{
		return (get_themed_color((p1.z + p2.z) >> 1, data->map->min_z,
				data->map->max_z, data->controls->color_theme));
	}
	if (data->controls->color_mode == 0)
		return (0xFFFFFF);
	return (color_functions[data->controls->color_mode & 0x03](p1, p2, data));
}

// Shape management and control
const char	*get_shape_name(t_shape_type shape)
{
	static const char	*shape_names[] = {
		"Flat", "Sphere", "Cylinder", "Cone", "Wave",
		"Torus", "Saddle", "Helix", "Ripple"
	};

	if (shape >= 0 && shape < NUM_SHAPES)
		return (shape_names[shape]);
	return ("Unknown");
}

const char	*get_shape_description(t_shape_type shape)
{
	static const char	*shape_descriptions[] = {
		"Standard flat 2D projection",
		"Maps points onto sphere surface",
		"Cylindrical surface projection",
		"Conical surface mapping",
		"Sinusoidal wave transformation",
		"Donut-shaped torus surface",
		"Hyperbolic saddle surface",
		"Spiral helix transformation",
		"Ripple effect transformation"
	};

	if (shape >= 0 && shape < NUM_SHAPES)
		return (shape_descriptions[shape]);
	return ("No description available");
}

t_shape_info	*get_shape_info(t_shape_type shape)
{
	static t_shape_info	shape_infos[] = {
		{"Flat", "Standard flat 2D projection", shape_flat_transform, 1.0f, 0.0f, 0},
		{"Sphere", "Maps points onto sphere surface", shape_sphere_transform, 50.0f, 0.0f, 0},
		{"Cylinder", "Cylindrical surface projection", shape_cylinder_transform, 30.0f, 0.0f, 0},
		{"Cone", "Conical surface mapping", shape_cone_transform, 40.0f, 0.0f, 0},
		{"Wave", "Sinusoidal wave transformation", shape_wave_transform, 20.0f, 0.0f, 1},
		{"Torus", "Donut-shaped torus surface", shape_torus_transform, 25.0f, 10.0f, 0},
		{"Saddle", "Hyperbolic saddle surface", shape_saddle_transform, 15.0f, 0.0f, 0},
		{"Helix", "Spiral helix transformation", shape_helix_transform, 30.0f, 0.0f, 1},
		{"Ripple", "Ripple effect transformation", shape_ripple_transform, 10.0f, 0.0f, 1}
	};

	if (shape >= 0 && shape < NUM_SHAPES)
		return (&shape_infos[shape]);
	return (NULL);
}