/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:39:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_shape_result shape_cone_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    float height_factor = (1.0f - params.norm_y);  // Cone gets smaller toward top
    float radius = 40.0f * params.scale * height_factor;
    float angle = params.norm_x * 2.0f * M_PI;
    (void)x;
    result.x = radius * cos(angle);
    result.z = z + radius * sin(angle) + params.offset;
    result.y = y + params.norm_y * 80.0f * params.scale;  // Height
    
    return (result);
}