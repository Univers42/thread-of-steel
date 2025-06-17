/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:23:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* ************************************************************************** */
/*                          COORDINATE CONVERSION UTILITIES                  */
/* ************************************************************************** */

// Coordinate conversion utilities
t_spherical cartesian_to_spherical(t_vec3 point)
{
    t_spherical result;
    
    result.r = vec3_length(point);
    if (result.r == 0.0f)
    {
        result.theta = 0.0f;
        result.phi = 0.0f;
        return (result);
    }
    
    result.theta = atan2f(point.y, point.x);
    result.phi = acosf(point.z / result.r);
    
    return (result);
}

t_vec3 spherical_to_cartesian(t_spherical sph)
{
    t_vec3 result;
    float sin_phi = fast_sin(sph.phi);
    
    result.x = sph.r * sin_phi * fast_cos(sph.theta);
    result.y = sph.r * sin_phi * fast_sin(sph.theta);
    result.z = sph.r * fast_cos(sph.phi);
    
    return (result);
}

t_cylindrical cartesian_to_cylindrical(t_vec3 point)
{
    t_cylindrical result;
    
    result.rho = fast_sqrt(point.x * point.x + point.y * point.y);
    result.phi = atan2f(point.y, point.x);
    result.z = point.z;
    
    return (result);
}

t_vec3 cylindrical_to_cartesian(t_cylindrical cyl)
{
    t_vec3 result;
    
    result.x = cyl.rho * fast_cos(cyl.phi);
    result.y = cyl.rho * fast_sin(cyl.phi);
    result.z = cyl.z;
    
    return (result);
}

void map_to_polar_coords(t_vec2 norm, t_map *map_info)
{
    if (!map_info)
        return;
    
    // Convert normalized coordinates to longitude/latitude
    map_info->lon = (int)(norm.x * 360.0f - 180.0f);
    map_info->lat = (int)(norm.y * 180.0f - 90.0f);
    
    // Clamp values to valid ranges
    if (map_info->lon < -180) map_info->lon = -180;
    if (map_info->lon > 180) map_info->lon = 180;
    if (map_info->lat < -90) map_info->lat = -90;
    if (map_info->lat > 90) map_info->lat = 90;
}

t_spherical spherical_lerp(t_spherical a, t_spherical b, float t)
{
    t_spherical result;
    
    result.r = lerp(a.r, b.r, t);
    result.theta = lerp(a.theta, b.theta, t);
    result.phi = lerp(a.phi, b.phi, t);
    
    return (result);
}

t_polar polar_from_normalized(t_vec2 norm, float max_radius)
{
    t_polar result;
    
    result.r = vec2_length(norm) * max_radius;
    result.theta = atan2f(norm.y, norm.x);
    
    return (result);
}

t_spherical spherical_add(t_spherical a, t_spherical b)
{
    // Convert to cartesian, add, then convert back
    t_vec3 cart_a = spherical_to_cartesian(a);
    t_vec3 cart_b = spherical_to_cartesian(b);
    t_vec3 sum = vec3_add(cart_a, cart_b);
    
    return (cartesian_to_spherical(sum));
}

/* ************************************************************************** */
/*                          PROJECTION UTILITIES                             */
/* ************************************************************************** */

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