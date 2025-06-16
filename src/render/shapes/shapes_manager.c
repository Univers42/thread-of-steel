/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:37:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Shape information table with function pointers and default parameters
static t_shape_info shape_table[NUM_SHAPES] = {
    {"Flat", shape_flat_transform, 1.0f, 0.0f},
    {"Sphere/Globe", shape_sphere_transform, 1.0f, 0.0f},
    {"Cylinder", shape_cylinder_transform, 1.0f, 0.0f},
    {"Cone", shape_cone_transform, 1.0f, 0.0f},
    {"Wave/Sine", shape_wave_transform, 1.0f, 0.0f},
    {"Torus/Donut", shape_torus_transform, 1.0f, 0.0f},
    {"Saddle/Pringles", shape_saddle_transform, 1.0f, 0.0f},
    {"Helix/Spiral", shape_helix_transform, 1.0f, 0.0f},
    {"Ripple/Concentric", shape_ripple_transform, 1.0f, 0.0f}
};

t_shape_info* get_shape_info(int shape)
{
    if (shape < 0 || shape >= NUM_SHAPES)
        return (&shape_table[0]); // Return flat as default
    return (&shape_table[shape]);
}

const char* get_shape_name(int shape)
{
    t_shape_info *info = get_shape_info(shape);
    return (info->name);
}

// Ultra-fast shape switching using lookup table
int handle_shape_switch(int key, int modifier, t_data *data)
{
    static int key_shape_map[256] = {0}; // Initialize all to 0
    static int map_initialized = 0;
    
    if (!map_initialized) {
        // Map Alt+digit keys to shapes
        key_shape_map[49] = 1;  // Alt+'1' -> Sphere
        key_shape_map[50] = 2;  // Alt+'2' -> Cylinder
        key_shape_map[51] = 3;  // Alt+'3' -> Cone
        key_shape_map[52] = 4;  // Alt+'4' -> Wave
        key_shape_map[53] = 5;  // Alt+'5' -> Torus
        key_shape_map[54] = 6;  // Alt+'6' -> Saddle
        key_shape_map[55] = 7;  // Alt+'7' -> Helix
        key_shape_map[56] = 8;  // Alt+'8' -> Ripple
        key_shape_map[57] = 0;  // Alt+'9' -> Flat (reset)
        map_initialized = 1;
    }
    
    // Check if Alt modifier is pressed using bitwise AND
    if (!(modifier & ALT_MASK))
        return (0);  // Not Alt+key combination
    
    // Only process if it's a valid shape key
    if (key >= 49 && key <= 57) // '1' to '9'
    {
        int new_shape = key_shape_map[key & 0xFF];
        data->controls->shape_mode = new_shape;
        
        // Print shape change notification
        ft_putstr_fd("Shape changed to: ", 1);
        ft_putendl_fd((char*)get_shape_name(new_shape), 1);
        
        // Redraw with new shape
        draw_map(data);
        return (1); // Key handled
    }
    
    return (0); // Key not handled
}

void cycle_shape(t_data *data)
{
    data->controls->shape_mode++;
    // Use bitwise operations for modulo (faster than %)
    if (data->controls->shape_mode >= NUM_SHAPES)
        data->controls->shape_mode = 0;
    
    ft_putstr_fd("Shape: ", 1);
    ft_putendl_fd((char*)get_shape_name(data->controls->shape_mode), 1);
    
    draw_map(data);
}

// Apply shape transformation to a point
t_point apply_shape_transform(t_point point, t_data *data)
{
    t_point transformed = point;
    t_shape_info *shape_info;
    t_shape_params params;
    t_shape_result result;
    
    // Skip transformation for flat shape (most common case)
    if (data->controls->shape_mode == SHAPE_FLAT)
        return (transformed);
    
    shape_info = get_shape_info(data->controls->shape_mode);
    
    // Skip if shape function not implemented yet
    if (!shape_info->transform)
        return (transformed);
    
    // Calculate normalized coordinates (0.0 to 1.0)
    params.norm_x = (float)(point.x + data->map->width / 2) / (float)data->map->width;
    params.norm_y = (float)(point.y + data->map->height / 2) / (float)data->map->height;
    params.map_width = data->map->width;
    params.map_height = data->map->height;
    params.scale = shape_info->default_scale;
    params.offset = shape_info->default_offset;
    
    // Clamp to valid range
    if (params.norm_x < 0.0f) params.norm_x = 0.0f;
    if (params.norm_x > 1.0f) params.norm_x = 1.0f;
    if (params.norm_y < 0.0f) params.norm_y = 0.0f;
    if (params.norm_y > 1.0f) params.norm_y = 1.0f;
    
    // Apply shape transformation using function pointer
    result = shape_info->transform((float)transformed.x, (float)transformed.y, 
                                   (float)transformed.z, params);
    
    transformed.x = (int)result.x;
    transformed.y = (int)result.y;
    transformed.z = (int)result.z;
    
    return (transformed);
}
