/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:09:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"

t_vec3 shape_sphere_transform(t_point point, t_shape_context context)
{
    t_vec3 result;
    
    // Calculate normalized coordinates (0.0 to 1.0)
    float norm_x = (float)(point.x + context.map_width / 2) / (float)context.map_width;
    float norm_y = (float)(point.y + context.map_height / 2) / (float)context.map_height;
    
    // Clamp to valid range
    if (norm_x < 0.0f) norm_x = 0.0f;
    if (norm_x > 1.0f) norm_x = 1.0f;
    if (norm_y < 0.0f) norm_y = 0.0f;
    if (norm_y > 1.0f) norm_y = 1.0f;
    
    // Convert to spherical coordinates
    t_spherical sph;
    sph.r = context.scale + (float)point.z * 0.3f; // Include height data
    sph.theta = norm_x * 2.0f * M_PI;  // Longitude (0 to 2π)
    sph.phi = norm_y * M_PI;           // Latitude (0 to π)
    
    // Convert spherical to cartesian using utility function
    result = spherical_to_cartesian(sph);
    result.z += context.offset;
    
    return (result);
}