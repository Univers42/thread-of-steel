/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:51:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 16:52:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int handle_close(void *param)
{
    t_data *data = (t_data *)param;
    
    if (data->map)
        free_map(data->map);
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->camera)
        free(data->camera);
    if (data->controls)
        free(data->controls);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    exit(0);
    return (0);
}

void free_map(t_map *map)
{
    int i;

    if (!map)
        return;
    if (map->points)
    {
        i = 0;
        while (i < map->height)
        {
            if (map->points[i])
                free(map->points[i]);
            i++;
        }
        free(map->points);
    }
    free(map);
}
