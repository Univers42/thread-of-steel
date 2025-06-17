/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_saddle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:05:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"

t_vec3 shape_saddle_transform(t_point point, t_shape_context context)
{
    t_vec3 result;
    
    // Calculate normalized coordinates
    float norm_x = (float)(point.x + context.map_width / 2) / (float)context.map_width;
    float norm_y = (float)(point.y + context.map_height / 2) / (float)context.map_height;
    
    // Clamp to valid range
    norm_x = (norm_x < 0.0f) ? 0.0f : (norm_x > 1.0f) ? 1.0f : norm_x;
    norm_y = (norm_y < 0.0f) ? 0.0f : (norm_y > 1.0f) ? 1.0f : norm_y;
    
    float scale = 30.0f * context.scale;
    float saddle_x = (norm_x - 0.5f) * 2.0f;  // -1 to 1
    float saddle_y = (norm_y - 0.5f) * 2.0f;  // -1 to 1
    
    result.x = (float)point.x;
    result.y = (float)point.y;
    result.z = (float)point.z + scale * (saddle_x * saddle_x - saddle_y * saddle_y) + context.offset;
    
    return (result);
}
