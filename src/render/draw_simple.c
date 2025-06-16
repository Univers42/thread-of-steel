/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:54:21 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 20:28:24 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_wireframe_grid(t_data *data)
{
    int x, y;
    t_point p1, p2;

    y = 0;
    while (y < data->map->height)
    {
        x = 0;
        while (x < data->map->width)
        {
            p1 = data->map->points[y][x];
            
            // Draw horizontal lines
            if (x < data->map->width - 1)
            {
                p2 = data->map->points[y][x + 1];
                draw_line(data, &p1, &p2);
            }
            
            // Draw vertical lines
            if (y < data->map->height - 1)
            {
                p2 = data->map->points[y + 1][x];
                draw_line(data, &p1, &p2);
            }
            x++;
        }
        y++;
    }
}

void clear_image(t_data *data)
{
    ft_memset(data->addr, 0, WIN_WIDTH * WIN_HEIGHT * (data->bits_per_pixel / 8));
}
