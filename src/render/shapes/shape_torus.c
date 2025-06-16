/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_torus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:39:57 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_shape_result shape_torus_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    float major_radius = 50.0f * params.scale;
    float minor_radius = 20.0f * params.scale;
    float theta = params.norm_x * 2.0f * M_PI;  // Around major radius
    float phi = params.norm_y * 2.0f * M_PI;    // Around minor radius
    (void)x;
    (void)y;
    result.x = (major_radius + minor_radius * cos(phi)) * cos(theta);
    result.y = (major_radius + minor_radius * cos(phi)) * sin(theta);
    result.z = z + minor_radius * sin(phi) + params.offset;
    
    return (result);
}