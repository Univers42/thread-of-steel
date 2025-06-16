/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:50:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:47:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int clip_line(t_point *p1, t_point *p2, int width, int height)
{
    // Simple line clipping - return 0 if line is completely outside bounds
    if ((p1->x < 0 && p2->x < 0) || (p1->x >= width && p2->x >= width) ||
        (p1->y < 0 && p2->y < 0) || (p1->y >= height && p2->y >= height))
        return (0);
    
    // Basic clipping to screen bounds
    if (p1->x < 0) p1->x = 0;
    if (p1->x >= width) p1->x = width - 1;
    if (p1->y < 0) p1->y = 0;
    if (p1->y >= height) p1->y = height - 1;
    
    if (p2->x < 0) p2->x = 0;
    if (p2->x >= width) p2->x = width - 1;
    if (p2->y < 0) p2->y = 0;
    if (p2->y >= height) p2->y = height - 1;
    
    return (1);
}

void draw_line_fast(t_data *data, t_point *p1, t_point *p2)
{
    // Apply shape transformations before projection
    t_point shaped_p1 = apply_shape_transform(*p1, data);
    t_point shaped_p2 = apply_shape_transform(*p2, data);
    
    t_point proj1 = project_point(shaped_p1, data->camera);
    t_point proj2 = project_point(shaped_p2, data->camera);
    
    // Aggressive culling for off-screen lines
    if ((proj1.x < -100 && proj2.x < -100) || 
        (proj1.x > WIN_WIDTH + 100 && proj2.x > WIN_WIDTH + 100) ||
        (proj1.y < -100 && proj2.y < -100) || 
        (proj1.y > WIN_HEIGHT + 100 && proj2.y > WIN_HEIGHT + 100))
        return;
    
    int dx = abs(proj2.x - proj1.x);
    int dy = abs(proj2.y - proj1.y);
    int sx = proj1.x < proj2.x ? 1 : -1;
    int sy = proj1.y < proj2.y ? 1 : -1;
    int err = dx - dy;
    
    int x = proj1.x;
    int y = proj1.y;
    int color = get_color(*p1, *p2, data);
    
    // Optimized Bresenham with minimal bounds checking
    while (1)
    {
        // Only draw pixels within screen bounds
        if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
        {
            // Direct memory access for speed
            *(unsigned int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8))) = color;
        }
        
        if (x == proj2.x && y == proj2.y)
            break;
            
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y += sy;
        }
    }
}

void draw_line(t_data *data, t_point *p1, t_point *p2)
{
    // Use fast version for better performance
    draw_line_fast(data, p1, p2);
}