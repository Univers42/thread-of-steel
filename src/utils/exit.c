/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:51:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:24:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int handle_close(void *param)
{
    t_data *data = (t_data *)param;
    
    // Proper cleanup order to prevent segfaults
    if (data->img)
    {
        mlx_destroy_image(data->mlx, data->img);
        data->img = NULL;
    }
    if (data->win)
    {
        mlx_destroy_window(data->mlx, data->win);
        data->win = NULL;
    }
    if (data->map)
    {
        free_map(data->map);
        data->map = NULL;
    }
    if (data->camera)
    {
        free(data->camera);
        data->camera = NULL;
    }
    if (data->controls)
    {
        free(data->controls);
        data->controls = NULL;
    }
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        data->mlx = NULL;
    }
    
    exit(0);
    return (0);
}

void free_map(t_map *map)
{
    if (!map)
        return ;
    
    if (map->points)
    {
        // Free the contiguous block of points first
        if (map->points[0])
            free(map->points[0]);
        
        // Then free the array of pointers
        free(map->points);
    }
    free(map);
}
