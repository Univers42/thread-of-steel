/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 13:26:05 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Helper function to convert map coordinates to polar coordinates
static void map_to_polar(float norm_x, float norm_y, int map_width, int map_height, 
                        float *longitude, float *latitude)
{
    // For proper sphere topology, we need full 2*PI longitude coverage
    float steps_x = (2.0f * M_PI) / map_width;  // Remove -1 to allow full wrap
    float steps_y = M_PI / (map_height - 1);    // Keep -1 for latitude (pole to pole)
    
    // Convert normalized coordinates back to map coordinates for polar calculation
    float map_x = norm_x * map_width;  // Don't center, use full range
    float map_y = norm_y * (map_height - 1);  // Use full range for latitude
    
    // Calculate longitude (around the sphere) - full 360° coverage
    *longitude = map_x * steps_x;
    
    // Calculate latitude (from north pole to south pole)
    *latitude = map_y * steps_y;
}

// Spherical transformation using proper polar coordinates
t_shape_result shape_sphere_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    
    (void)x; // Suppress unused parameter warning
    (void)y; // Suppress unused parameter warning
    
    // Calculate sphere radius based on map dimensions
    float base_radius = (params.map_width / (2.0f * M_PI)) * params.scale * 30.0f;
    
    // Convert normalized coordinates to polar coordinates
    float longitude, latitude;
    map_to_polar(params.norm_x, params.norm_y, params.map_width, params.map_height,
                &longitude, &latitude);
    
    // Apply spherical transformation: (radius + z) to include original height data
    float sphere_radius = base_radius + z * 0.3f; // Reduced scale for better proportion
    
    // Handle pole singularities - at poles (latitude = 0 or PI), longitude becomes irrelevant
    if (latitude < 0.01f || latitude > M_PI - 0.01f)
    {
        // At poles, collapse all longitude values to center
        result.x = 0.0f;
        result.y = 0.0f;
        if (latitude < 0.01f)
            result.z = sphere_radius + params.offset;  // North pole
        else
            result.z = -sphere_radius + params.offset; // South pole
    }
    else
    {
        // Normal spherical coordinate conversion to Cartesian
        result.x = sphere_radius * sin(latitude) * cos(longitude);
        result.y = sphere_radius * sin(latitude) * sin(longitude);
        result.z = sphere_radius * cos(latitude) + params.offset;
    }
    
    return (result);
}
