/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:37:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_shape_result shape_cylinder_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    float radius = 40.0f * params.scale;
    float angle = params.norm_x * 2.0f * M_PI;  // Full circle
    
    (void)x; // Suppress unused parameter warning
    
    result.x = radius * cos(angle);
    result.z = z + radius * sin(angle) + params.offset;
    result.y = y + params.norm_y * 60.0f * params.scale;  // Height along Y axis
    
    return (result);
}
