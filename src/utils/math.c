/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:13:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/* ************************************************************************** */
/*                          BASIC MATHEMATICAL OPERATIONS                    */
/* ************************************************************************** */

float	point_distance_2d(t_vec2 coord1, t_vec2 coord2)
{
	float	dx;
	float	dy;

	dx = coord2.x - coord1.x;
	dy = coord2.y - coord1.y;
	return (fast_sqrt(dx * dx + dy * dy));
}

float	smooth_step(float edge0, float edge1, float x)
{
	if (x <= edge0)
		return (0.0f);
	if (x >= edge1)
		return (1.0f);
	x = (x - edge0) / (edge1 - edge0);
	return (x * x * (3.0f - 2.0f * x));
}

float	lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

/* ************************************************************************** */
/*                          ADVANCED MATHEMATICAL FUNCTIONS                  */
/* ************************************************************************** */

float	clamp(float value, float min_val, float max_val)
{
	if (value < min_val)
		return (min_val);
	if (value > max_val)
		return (max_val);
	return (value);
}

float	fast_inv_sqrt(float x)
{
	float	half_x;
	int		i;

	half_x = 0.5f * x;
	i = *(int *)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float *)&i;
	x = x * (1.5f - half_x * x * x);
	return (x);
}

float	smoother_step(float edge0, float edge1, float x)
{
	if (x <= edge0)
		return (0.0f);
	if (x >= edge1)
		return (1.0f);
	x = (x - edge0) / (edge1 - edge0);
	return (x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f));
}

float	wrap_angle(float angle)
{
	while (angle < 0.0f)
		angle += 2.0f * M_PI;
	while (angle >= 2.0f * M_PI)
		angle -= 2.0f * M_PI;
	return (angle);
}

float	map_range(float value, float from_min, float from_max,
					float to_min, float to_max)
{
	return (to_min + (value - from_min) * (to_max - to_min)
		/ (from_max - from_min));
}