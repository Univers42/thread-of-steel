/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:19:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Color utilities
int interpolate_color(int color1, int color2, float t)
{
    if (t <= 0.0f) return (color1);
    if (t >= 1.0f) return (color2);
    
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;
    
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;
    
    int r = (int)(r1 + t * (r2 - r1));
    int g = (int)(g1 + t * (g2 - g1));
    int b = (int)(b1 + t * (b2 - b1));
    
    return ((r << 16) | (g << 8) | b);
}

int get_gradient_color(float value, float min_val, float max_val, int color1, int color2)
{
    if (max_val == min_val)
        return (color1);
    
    float t = (value - min_val) / (max_val - min_val);
    return (interpolate_color(color1, color2, t));
}

// Map utilities
void calculate_map_bounds(t_map *map)
{
    if (!map || !map->points)
        return;
    
    map->min_z = map->points[0][0].z;
    map->max_z = map->points[0][0].z;
    
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if (map->points[y][x].z < map->min_z)
                map->min_z = map->points[y][x].z;
            if (map->points[y][x].z > map->max_z)
                map->max_z = map->points[y][x].z;
        }
    }
}

t_vec2 get_map_center(t_map *map)
{
    t_vec2 center;
    
    if (!map)
    {
        center.x = 0.0f;
        center.y = 0.0f;
        return (center);
    }
    
    center.x = (float)map->width / 2.0f;
    center.y = (float)map->height / 2.0f;
    
    return (center);
}

float get_map_scale_factor(t_map *map, int window_width, int window_height)
{
    if (!map)
        return (1.0f);
    
    float width_ratio = (float)(window_width - FIT_MARGIN * 2) / (float)map->width;
    float height_ratio = (float)(window_height - FIT_MARGIN * 2) / (float)map->height;
    
    return (width_ratio < height_ratio ? width_ratio : height_ratio);
}

// Projection utilities
t_point isometric_project(t_vec3 point)
{
    t_point result;
    
    // Standard isometric projection angles (30 degrees)
    const float cos30 = 0.866025f;
    const float sin30 = 0.5f;
    
    result.x = (int)((point.x - point.y) * cos30);
    result.y = (int)((point.x + point.y) * sin30 - point.z);
    result.z = (int)point.z;
    result.color = DEFAULT_COLOR;
    
    return (result);
}

t_point perspective_project(t_vec3 point, float fov, float aspect)
{
    t_point result;
    float z_distance = point.z + 100.0f; // Prevent division by zero
    
    if (z_distance <= 0.0f)
        z_distance = 1.0f;
    
    float scale = 1.0f / tanf(fov * 0.5f * M_PI / 180.0f);
    
    result.x = (int)(point.x * scale / z_distance);
    result.y = (int)(point.y * scale / (z_distance * aspect));
    result.z = (int)point.z;
    result.color = DEFAULT_COLOR;
    
    return (result);
}
