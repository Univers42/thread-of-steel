/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_helix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:40:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_shape_result shape_helix_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    float radius = 30.0f * params.scale;
    float angle = params.norm_x * 6.0f * M_PI;  // Multiple turns
    float height_scale = 80.0f * params.scale;
    (void)x;
    result.x = radius * cos(angle);
    result.z = z + radius * sin(angle) + params.offset;
    result.y = y + params.norm_y * height_scale;
    
    return (result);
}