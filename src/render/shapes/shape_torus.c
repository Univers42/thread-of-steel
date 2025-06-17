/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_torus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:05:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"

t_vec3 shape_torus_transform(t_point point, t_shape_context context)
{
    t_vec3 result;
    
    // Calculate normalized coordinates
    float norm_x = (float)(point.x + context.map_width / 2) / (float)context.map_width;
    float norm_y = (float)(point.y + context.map_height / 2) / (float)context.map_height;
    
    // Clamp to valid range
    norm_x = (norm_x < 0.0f) ? 0.0f : (norm_x > 1.0f) ? 1.0f : norm_x;
    norm_y = (norm_y < 0.0f) ? 0.0f : (norm_y > 1.0f) ? 1.0f : norm_y;
    
    float major_radius = 50.0f * context.scale;
    float minor_radius = 20.0f * context.scale;
    float theta = norm_x * 2.0f * M_PI;  // Around major radius
    float phi = norm_y * 2.0f * M_PI;    // Around minor radius
    
    result.x = (major_radius + minor_radius * fast_cos(phi)) * fast_cos(theta);
    result.y = (major_radius + minor_radius * fast_cos(phi)) * fast_sin(theta);
    result.z = (float)point.z + minor_radius * fast_sin(phi) + context.offset;
    
    return (result);
}