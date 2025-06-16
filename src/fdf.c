/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:36:56 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 12:41:11 by dlesieur         ###   ########.fr       */
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
typedef struct s_data
{
    void    *mlx;
    void    *win1;
    void    *win2;
}   t_data;

int handle_keypress(int keycode, void *param)
{
    t_data *data = (t_data *)param;
    
    if (keycode == 65307) // ESC key
    {
        // Clean shutdown
        mlx_destroy_window(data->mlx, data->win1);
        mlx_destroy_window(data->mlx, data->win2);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(0);
    }
    return (0);
}

int handle_close(void *param)
{
    t_data *data = (t_data *)param;
    
    mlx_destroy_window(data->mlx, data->win1);
    mlx_destroy_window(data->mlx, data->win2);
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
    data.win1 = mlx_new_window(data.mlx, 600, 400, "My first window");
    data.win2 = mlx_new_window(data.mlx, 600, 400, "window2");
    
    // Set up event handlers - pass the data structure
    mlx_key_hook(data.win1, handle_keypress, &data);
    mlx_hook(data.win1, 17, 0, handle_close, &data);
    
    mlx_loop(data.mlx);
    
    // This code won't be reached due to mlx_loop, but good practice
    mlx_destroy_window(data.mlx, data.win1);
    mlx_destroy_window(data.mlx, data.win2);
    return (0);
}