/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:05:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"

t_vec3 shape_cone_transform(t_point point, t_shape_context context)
{
    t_vec3 result;
    
    // Calculate normalized coordinates
    float norm_x = (float)(point.x + context.map_width / 2) / (float)context.map_width;
    float norm_y = (float)(point.y + context.map_height / 2) / (float)context.map_height;
    
    // Clamp to valid range
    norm_x = (norm_x < 0.0f) ? 0.0f : (norm_x > 1.0f) ? 1.0f : norm_x;
    norm_y = (norm_y < 0.0f) ? 0.0f : (norm_y > 1.0f) ? 1.0f : norm_y;
    
    float height_factor = (1.0f - norm_y);  // Cone gets smaller toward top
    float radius = 40.0f * context.scale * height_factor;
    float angle = norm_x * 2.0f * M_PI;
    
    result.x = radius * fast_cos(angle);
    result.z = (float)point.z + radius * fast_sin(angle) + context.offset;
    result.y = (float)point.y + norm_y * 80.0f * context.scale;  // Height
    
    return (result);
}