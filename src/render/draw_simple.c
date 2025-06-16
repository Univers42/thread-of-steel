/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:08:14 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 14:29:34 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_simple_object(t_data *data)
{
    int i;

    i = -11;
    while (++i <= 10)
        mlx_pixel_put(data->mlx, data->win, data->x + i, data->y, data->color);
    i = -11;
    while (++i <= 10)
        mlx_pixel_put(data->mlx, data->win, data->x, data->y + i, data->color);
}

int handle_keypress(int keycode, void *param)
{
    t_data *data = (t_data *)param;
    
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(0);
    }
    else if (keycode == KEY_LEFT)
    {
        data->x -= 10;
        mlx_clear_window(data->mlx, data->win);
        draw_simple_object(data);
    }
    else if (keycode == KEY_RIGHT)
    {
        data->x += 10;
        mlx_clear_window(data->mlx, data->win);
        draw_simple_object(data);
    }
    else if (keycode == KEY_UP)
    {
        data->y -= 10;
        mlx_clear_window(data->mlx, data->win);
        draw_simple_object(data);
    }
    else if (keycode == KEY_DOWN)
    {
        data->y += 10;
        mlx_clear_window(data->mlx, data->win);
        draw_simple_object(data);
    }
    else if (keycode == KEY_C)
    {
        data->color = (data->color == 0xFF0000) ? 0x00FF00 : 0xFF0000;
        mlx_clear_window(data->mlx, data->win);
        draw_simple_object(data);
    }
    return (0);
}