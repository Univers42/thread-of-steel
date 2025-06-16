/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_ripple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:38:55 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_shape_result shape_ripple_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    float center_x = 0.5f;
    float center_y = 0.5f;
    float distance = sqrt((params.norm_x - center_x) * (params.norm_x - center_x) + 
                         (params.norm_y - center_y) * (params.norm_y - center_y));
    
    float ripple = sin(distance * 20.0f * M_PI) * 15.0f * params.scale * exp(-distance * 3.0f);
    
    result.x = x;
    result.y = y;
    result.z = z + ripple + params.offset;
    
    return (result);
}