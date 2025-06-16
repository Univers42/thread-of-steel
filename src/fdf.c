/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:36:56 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 14:28:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
/**
 * !TO REMEMBER
 * each window needs its own identifier to draw in its specific events
 * ne need mlx_loop(mlx) to keep the windowsn alive and responsive
 * 
 */


int handle_close(void *param)
{
    t_data *data = (t_data *)param;
    
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
    return (0);
}

int main()
{
    t_data data;
    
    // mlx_init called to establish connections
    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    
    // Open different windows on the same connection
    data.win = mlx_new_window(data.mlx, 600, 400, "My first window");
    if (!data.win)
    {
        mlx_destroy_display(data.mlx);
        free(data.mlx);
        return (1);
    }
    
    data.x = 400;
    data.y = 300;
    data.color = 0xFF0000;
    draw_simple_object(&data);
    
    // Set up event handlers - pass the data structure
    mlx_key_hook(data.win, handle_keypress, &data);
    mlx_hook(data.win, 17, 0, handle_close, &data);
    mlx_loop(data.mlx);
    return (0);
}