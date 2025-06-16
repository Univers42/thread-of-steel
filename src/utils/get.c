/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:51:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 16:51:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int get_color(t_point p1, t_point p2, t_data *data)
{
    int color;

    if (data->controls->color_mode == 0)
        return (0xFFFFFF);
    else if (data->controls->color_mode == 1)
    {
        int avg_z = (p1.z + p2.z) / 2;
        int z_range = data->map->max_z - data->map->min_z;
        if (z_range == 0)
            return (0xFFFFFF);
        
        float ratio = (float)(avg_z - data->map->min_z) / z_range;
        if (ratio < 0.5)
            color = (int)(ratio * 2 * 255) << 8;
        else
            color = 0xFF0000 | ((int)((1 - ratio) * 2 * 255) << 8);
        return (color);
    }
    else if (data->controls->color_mode == 2)
    {
        static int hue = 0;
        hue = (hue + 1) % 360;
        return (0xFF0000 | (hue << 8) | ((360 - hue) << 16));
    }
    return (0xFFFFFF);
}




