/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:49:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:08:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_movement_keys(int key, t_data *data)
{
	if (key == KEY_W || key == KEY_UP)
		data->camera->offset_y -= 20;
	else if (key == KEY_S || key == KEY_DOWN)
		data->camera->offset_y += 20;
	else if (key == KEY_A || key == KEY_LEFT)
		data->camera->offset_x -= 20;
	else if (key == KEY_D || key == KEY_RIGHT)
		data->camera->offset_x += 20;
}

static void	handle_rotation_keys(int key, t_data *data)
{
	if (key == KEY_Q)
		data->camera->angle_z -= 0.05;
	else if (key == KEY_E)
		data->camera->angle_z += 0.05;
	else if (key == KEY_R)
		data->camera->angle_x -= 0.05;
	else if (key == KEY_T)
		data->camera->angle_x += 0.05;
}

static void	handle_zoom_keys(int key, t_data *data)
{
	if (key == KEY_PLUS)
		data->camera->zoom *= 1.2;
	else if (key == KEY_MINUS)
		data->camera->zoom *= 0.8;
	else if (key == KEY_Z)
	{
		data->camera->z_scale += 0.2;
		if (data->camera->z_scale > 10)
			data->camera->z_scale = 10;
	}
	else if (key == KEY_X)
	{
		data->camera->z_scale -= 0.2;
		if (data->camera->z_scale < 0.1)
			data->camera->z_scale = 0.1;
	}
}

static void	handle_mode_keys(int key, t_data *data)
{
	if (key == KEY_SPACE)
		data->controls->color_mode = (data->controls->color_mode + 1) % 3;
	else if (key == KEY_TAB)
	{
		if (data->controls->alt_pressed)
			cycle_shape(data);
		else
			cycle_color_theme(data);
	}
}

int	handle_keypress(int key, t_data *data)
{
	int	modifier;

	modifier = 0;
	if (data->controls->alt_pressed)
		modifier |= ALT_MASK;
	if (handle_shape_switch(key, modifier, data))
		return (0);
	if (handle_theme_switch(key, data))
		return (0);
	if (key == KEY_ALT_L || key == KEY_ALT_R)
	{
		data->controls->alt_pressed = 1;
		return (0);
	}
	if (key == KEY_ESC)
	{
		handle_close(data);
		return (0);
	}
	handle_movement_keys(key, data);
	handle_rotation_keys(key, data);
	handle_zoom_keys(key, data);
	handle_mode_keys(key, data);
	draw_map(data);
	return (0);
}

int	handle_keyrelease(int key, t_data *data)
{
	if (key == KEY_ALT_L || key == KEY_ALT_R)
		data->controls->alt_pressed = 0;
	return (0);
}