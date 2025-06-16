/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_saddle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:37:21 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_shape_result shape_saddle_transform(float x, float y, float z, t_shape_params params)
{
    t_shape_result result;
    float scale = 30.0f * params.scale;
    float saddle_x = (params.norm_x - 0.5f) * 2.0f;  // -1 to 1
    float saddle_y = (params.norm_y - 0.5f) * 2.0f;  // -1 to 1
    
    result.x = x;
    result.y = y;
    result.z = z + scale * (saddle_x * saddle_x - saddle_y * saddle_y) + params.offset;
    
    return (result);
}
