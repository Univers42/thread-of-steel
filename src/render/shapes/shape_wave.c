/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_wave.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:37:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_shape_result shape_wave_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    float wave_amplitude = 20.0f * params.scale;
    
    // Sine wave in both X and Y directions
    float wave_x = sin(params.norm_x * 4.0f * M_PI) * wave_amplitude;
    float wave_y = sin(params.norm_y * 4.0f * M_PI) * wave_amplitude;
    
    result.x = x;
    result.y = y;
    result.z = z + wave_x + wave_y + params.offset;
    
    return (result);
}
