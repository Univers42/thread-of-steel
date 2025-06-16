/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:08:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:47:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int calculate_lod(float zoom)
{
    if (zoom < 2.0f) return 3;      // Very zoomed out - draw every 8th line
    if (zoom < 5.0f) return 2;      // Zoomed out - draw every 4th line  
    if (zoom < 10.0f) return 1;     // Normal - draw every 2nd line
    return 0;                       // Zoomed in - draw all lines
}

int is_line_visible(t_point p1, t_point p2, int width, int height)
{
    // Quick bounds check - if both points are completely outside, skip
    if ((p1.x < -100 && p2.x < -100) || (p1.x > width + 100 && p2.x > width + 100) ||
        (p1.y < -100 && p2.y < -100) || (p1.y > height + 100 && p2.y > height + 100))
        return (0);
    return (1);
}

int calculate_view_hash(t_data *data)
{
    // Simple hash of camera parameters for conditional rendering
    return ((int)(data->camera->zoom * 1000) ^ 
            (int)(data->camera->angle_x * 1000) ^ 
            (int)(data->camera->angle_y * 1000) ^ 
            (int)(data->camera->angle_z * 1000) ^
            (int)data->camera->offset_x ^ 
            (int)data->camera->offset_y ^
            (int)(data->camera->trackball_quat[0] * 1000) ^
            (int)(data->camera->trackball_quat[1] * 1000));
}

static void draw_wireframe_complete(t_data *data)
{
    int x, y;
    t_point p1, p2;

    // Draw all horizontal and vertical connections
    y = 0;
    while (y < data->map->height)
    {
        x = 0;
        while (x < data->map->width)
        {
            p1 = data->map->points[y][x];
            
            // Draw horizontal lines (connect to right neighbor)
            if (x < data->map->width - 1)
            {
                p2 = data->map->points[y][x + 1];
                draw_line(data, &p1, &p2);
            }
            
            // Draw vertical lines (connect to bottom neighbor)
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

static void draw_wireframe_lod(t_data *data)
{
    if (!data || !data->map || !data->camera)
        return;
        
    int x, y;
    t_point p1, p2;
    int lod = calculate_lod(data->camera->zoom);
    int step = 1 << lod; // 1, 2, 4, 8...
    
    // Skip very small steps for performance
    if (step < 1) step = 1;
    
    // Draw with level of detail - skip lines based on zoom level
    for (y = 0; y < data->map->height - step; y += step)
    {
        for (x = 0; x < data->map->width - step; x += step)
        {
            if (y >= data->map->height || x >= data->map->width)
                continue;
                
            p1 = data->map->points[y][x];
            
            // Draw horizontal lines
            if (x + step < data->map->width)
            {
                p2 = data->map->points[y][x + step];
                t_point proj1 = project_point(p1, data->camera);
                t_point proj2 = project_point(p2, data->camera);
                
                if (is_line_visible(proj1, proj2, WIN_WIDTH, WIN_HEIGHT))
                    draw_line_fast(data, &p1, &p2);
            }
            
            // Draw vertical lines  
            if (y + step < data->map->height)
            {
                p2 = data->map->points[y + step][x];
                t_point proj1 = project_point(p1, data->camera);
                t_point proj2 = project_point(p2, data->camera);
                
                if (is_line_visible(proj1, proj2, WIN_WIDTH, WIN_HEIGHT))
                    draw_line_fast(data, &p1, &p2);
            }
        }
    }
}

void draw_map_optimized(t_data *data)
{
    if (!data || !data->addr || !data->map)
        return;
    
    // Fast memory clear using memset - more efficient than pixel-by-pixel
    ft_memset(data->addr, 0, data->line_length * WIN_HEIGHT);
    
    // Use LOD for large maps, full rendering for small maps
    if (data->map->width * data->map->height > 10000) // Large map threshold
        draw_wireframe_lod(data);
    else
        draw_wireframe_complete(data);
    
    // Display the rendered image immediately to prevent flickering
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void draw_map(t_data *data)
{
    // Always use optimized version for consistent performance
    draw_map_optimized(data);
}
