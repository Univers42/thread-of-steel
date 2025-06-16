/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:36:56 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 12:22:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * !TO REMEMBER
 * each window needs its own identifier to draw in its specific events
 * ne need mlx_loop(mlx) to keep the windowsn alive and responsive
 * 
 */
int	main()
{
    void    *mlx;
    void    *win1;
    void    *win2;
    // mlx_init called to establish connections
    mlx = mlx_init();
    if(!mlx)
        return (1);
    //we open different window called on the same connection
    win1 = mlx_new_window(mlx, 600, 400, "My first window");
    win2 = mlx_new_window(mlx, 600, 400, "window2");
    (void) win1;
    (void) win2;
    mlx_loop(mlx);
    return (0);
}