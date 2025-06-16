/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:37:23 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_shape_result shape_sphere_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    float radius = 50.0f * params.scale;
    float theta = params.norm_x * M_PI;        // 0 to PI
    float phi = params.norm_y * 2.0f * M_PI;   // 0 to 2*PI
    
    (void)x; // Suppress unused parameter warning
    (void)y; // Suppress unused parameter warning
    
    result.x = radius * sin(theta) * cos(phi);
    result.y = radius * sin(theta) * sin(phi);
    result.z = z + radius * cos(theta) + params.offset;
    
    return (result);
}
