/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 13:22:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "shapes.h"

// Shape transformation functions using efficient mathematical operations
void shape_flat(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)norm_x; (void)norm_y; (void)width; (void)height;
    // No transformation - keep original coordinates
    (void)x; (void)y; (void)z;
}

void shape_sphere(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)width; (void)height;
    float radius = 50.0f;
    float theta = norm_x * M_PI;        // 0 to PI
    float phi = norm_y * 2.0f * M_PI;   // 0 to 2*PI
    
    *x = radius * sin(theta) * cos(phi);
    *y = radius * sin(theta) * sin(phi);
    *z = *z + radius * cos(theta);
}

void shape_cylinder(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)width; (void)height;
    float radius = 40.0f;
    float angle = norm_x * 2.0f * M_PI;  // Full circle
    
    *x = radius * cos(angle);
    *z = *z + radius * sin(angle);
    *y = *y + norm_y * 60.0f;  // Height along Y axis
}

void shape_cone(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)width; (void)height;
    float height_factor = (1.0f - norm_y);  // Cone gets smaller toward top
    float radius = 40.0f * height_factor;
    float angle = norm_x * 2.0f * M_PI;
    
    *x = radius * cos(angle);
    *z = *z + radius * sin(angle);
    *y = *y + norm_y * 80.0f;  // Height
}

void shape_wave(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)width; (void)height;
    // Sine wave in both X and Y directions
    float wave_x = sin(norm_x * 4.0f * M_PI) * 20.0f;
    float wave_y = sin(norm_y * 4.0f * M_PI) * 20.0f;
    
    *z = *z + wave_x + wave_y;
    // Keep X,Y relatively unchanged for wave effect
}

void shape_torus(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)width; (void)height;
    float major_radius = 50.0f;
    float minor_radius = 20.0f;
    float theta = norm_x * 2.0f * M_PI;  // Around major radius
    float phi = norm_y * 2.0f * M_PI;    // Around minor radius
    
    *x = (major_radius + minor_radius * cos(phi)) * cos(theta);
    *y = (major_radius + minor_radius * cos(phi)) * sin(theta);
    *z = *z + minor_radius * sin(phi);
}

void shape_saddle(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)width; (void)height;
    // Hyperbolic paraboloid (Pringles shape)
    float scale = 30.0f;
    float saddle_x = (norm_x - 0.5f) * 2.0f;  // -1 to 1
    float saddle_y = (norm_y - 0.5f) * 2.0f;  // -1 to 1
    
    *z = *z + scale * (saddle_x * saddle_x - saddle_y * saddle_y);
}

void shape_helix(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)width; (void)height;
    float radius = 30.0f;
    float angle = norm_x * 6.0f * M_PI;  // Multiple turns
    float height_scale = 80.0f;
    
    *x = radius * cos(angle);
    *z = *z + radius * sin(angle);
    *y = *y + norm_y * height_scale;
}

void shape_ripple(float *x, float *y, float *z, float norm_x, float norm_y, int width, int height)
{
    (void)width; (void)height;
    // Ripple effect from center
    float center_x = 0.5f;
    float center_y = 0.5f;
    float distance = sqrt((norm_x - center_x) * (norm_x - center_x) + 
                         (norm_y - center_y) * (norm_y - center_y));
    
    float ripple = sin(distance * 20.0f * M_PI) * 15.0f * exp(-distance * 3.0f);
    *z = *z + ripple;
}

// Ultra-fast shape selection using function pointer table
static shape_func_t shape_functions[NUM_SHAPES] = {
    shape_flat,     // 0
    shape_sphere,   // 1 
    shape_cylinder, // 2
    shape_cone,     // 3
    shape_wave,     // 4
    shape_torus,    // 5
    shape_saddle,   // 6
    shape_helix,    // 7
    shape_ripple    // 8
};

// Shape names lookup table
static const char* shape_names[NUM_SHAPES] = {
    "Flat",
    "Sphere/Globe",
    "Cylinder", 
    "Cone",
    "Wave/Sine",
    "Torus/Donut",
    "Saddle/Pringles",
    "Helix/Spiral",
    "Ripple/Concentric"
};

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
    
    // Bounds check using bitwise AND
    int new_shape = key_shape_map[key & 0xFF];
    
    // Only process if it's a valid shape key
    if (key >= 49 && key <= 57) // '1' to '9'
    {
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

const char* get_shape_name(int shape)
{
    return shape_names[shape & 0x0F];  // Bitwise AND for bounds checking
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
    
    // Skip transformation for flat shape (most common case)
    if (data->controls->shape_mode == SHAPE_FLAT)
        return transformed;
    
    // Calculate normalized coordinates (0.0 to 1.0)
    float norm_x = (float)(point.x + data->map->width / 2) / (float)data->map->width;
    float norm_y = (float)(point.y + data->map->height / 2) / (float)data->map->height;
    
    // Clamp to valid range
    if (norm_x < 0.0f) norm_x = 0.0f;
    if (norm_x > 1.0f) norm_x = 1.0f;
    if (norm_y < 0.0f) norm_y = 0.0f;
    if (norm_y > 1.0f) norm_y = 1.0f;
    
    // Apply shape transformation using function pointer
    float x = (float)transformed.x;
    float y = (float)transformed.y;
    float z = (float)transformed.z;
    
    shape_functions[data->controls->shape_mode & 0x0F](&x, &y, &z, norm_x, norm_y, 
                                                       data->map->width, data->map->height);
    
    transformed.x = (int)x;
    transformed.y = (int)y;
    transformed.z = (int)z;
    
    return transformed;
}