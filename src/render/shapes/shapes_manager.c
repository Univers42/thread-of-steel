/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:17:41 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"


// Ultra-fast shape switching using lookup table
static int	init_shape_key_map(int key_shape_map[256])
{
	int	i;

	i = 0;
	while (i < 256)
		key_shape_map[i++] = 0;
	key_shape_map[49] = 1;
	key_shape_map[50] = 2;
	key_shape_map[51] = 3;
	key_shape_map[52] = 4;
	key_shape_map[53] = 5;
	key_shape_map[54] = 6;
	key_shape_map[55] = 7;
	key_shape_map[56] = 8;
	key_shape_map[57] = 0;
	return (1);
}

int	handle_shape_switch(int key, int modifier, t_data *data)
{
	static int		key_shape_map[256];
	static int		map_initialized = 0;
	t_shape_type	new_shape;

	if (!map_initialized)
		map_initialized = init_shape_key_map(key_shape_map);
	if (!(modifier & ALT_MASK))
		return (0);
	if (key >= 49 && key <= 57)
	{
		new_shape = key_shape_map[key & 0xFF];
		data->controls->shape_mode = new_shape;
		ft_putstr_fd("Shape changed to: ", 1);
		ft_putendl_fd((char *)get_shape_name(new_shape), 1);
		draw_map(data);
		return (1);
	}
	return (0);
}

void	cycle_shape(t_data *data)
{
	data->controls->shape_mode++;
	if (data->controls->shape_mode >= NUM_SHAPES)
		data->controls->shape_mode = 0;
	ft_putstr_fd("Shape: ", 1);
	ft_putendl_fd((char *)get_shape_name(data->controls->shape_mode), 1);
	draw_map(data);
}

// Apply shape transformation to a point using new unified system
t_point	apply_shape_transform(t_point point, t_data *data)
{
	t_point			transformed;
	t_shape_info	*shape_info;
	t_shape_context	context;
	t_vec3			result;

	transformed = point;
	if (data->controls->shape_mode == SHAPE_TYPE_FLAT)
		return (transformed);
	shape_info = get_shape_info(data->controls->shape_mode);
	if (!shape_info->transform)
		return (transformed);
	context.map_width = data->map->width;
	context.map_height = data->map->height;
	context.scale = shape_info->default_scale;
	context.offset = shape_info->default_offset;
	context.time = 0.0f;
	result = shape_info->transform(point, context);
	transformed.x = (int)result.x;
	transformed.y = (int)result.y;
	transformed.z = (int)result.z;
	return (transformed);
}