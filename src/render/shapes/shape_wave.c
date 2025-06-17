/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_wave.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:50:13 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"

t_vec3 shape_wave_transform(t_point point, t_shape_context context)
{
    t_vec3 result;
    
    // Calculate normalized coordinates
    float norm_x = (float)(point.x + context.map_width / 2) / (float)context.map_width;
    float norm_y = (float)(point.y + context.map_height / 2) / (float)context.map_height;
    
    // Clamp to valid range
    norm_x = (norm_x < 0.0f) ? 0.0f : (norm_x > 1.0f) ? 1.0f : norm_x;
    norm_y = (norm_y < 0.0f) ? 0.0f : (norm_y > 1.0f) ? 1.0f : norm_y;
    
    float wave_amplitude = 20.0f * context.scale;
    
    // Sine wave in both X and Y directions
    float wave_x = fast_sin(norm_x * 4.0f * M_PI) * wave_amplitude;
    float wave_y = fast_sin(norm_y * 4.0f * M_PI) * wave_amplitude;
    
    result.x = (float)point.x;
    result.y = (float)point.y;
    result.z = (float)point.z + wave_x + wave_y + context.offset;
    
    return (result);
}
