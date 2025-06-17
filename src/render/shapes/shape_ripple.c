/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_ripple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:05:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"

t_vec3 shape_ripple_transform(t_point point, t_shape_context context)
{
    t_vec3 result;
    
    // Calculate normalized coordinates
    float norm_x = (float)(point.x + context.map_width / 2) / (float)context.map_width;
    float norm_y = (float)(point.y + context.map_height / 2) / (float)context.map_height;
    
    // Clamp to valid range
    norm_x = (norm_x < 0.0f) ? 0.0f : (norm_x > 1.0f) ? 1.0f : norm_x;
    norm_y = (norm_y < 0.0f) ? 0.0f : (norm_y > 1.0f) ? 1.0f : norm_y;
    
    float center_x = 0.5f;
    float center_y = 0.5f;
    float distance = fast_sqrt((norm_x - center_x) * (norm_x - center_x) + 
                               (norm_y - center_y) * (norm_y - center_y));
    
    float ripple = fast_sin(distance * 20.0f * M_PI) * 15.0f * context.scale * expf(-distance * 3.0f);
    
    result.x = (float)point.x;
    result.y = (float)point.y;
    result.z = (float)point.z + ripple + context.offset;
    
    return (result);
}