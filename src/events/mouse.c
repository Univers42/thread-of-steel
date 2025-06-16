/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:48:57 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 20:53:29 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int handle_mouse_press(int button, int x, int y, t_data *data)
{
    if (button == MOUSE_LEFT)
    {
        data->controls->mouse_pressed = 1;
        data->controls->last_mouse_x = x;
        data->controls->last_mouse_y = y;
    }
    else if (button == MOUSE_WHEEL_UP)
    {
        data->camera->zoom *= MOUSE_ZOOM_SENSITIVITY;
        draw_map(data);
    }
    else if (button == MOUSE_WHEEL_DOWN)
    {
        data->camera->zoom /= MOUSE_ZOOM_SENSITIVITY;
        if (data->camera->zoom < 1.0)
            data->camera->zoom = 1.0;
        draw_map(data);
    }
    return (0);
}

int handle_mouse_release(int button, int x, int y, t_data *data)
{
    (void)x;
    (void)y;
    if (button == MOUSE_LEFT)
        data->controls->mouse_pressed = 0;
    return (0);
}

int handle_mouse_move(int x, int y, t_data *data)
{
    if (data->controls->mouse_pressed)
    {
        // Calculate mouse movement delta
        int dx = x - data->controls->last_mouse_x;
        int dy = y - data->controls->last_mouse_y;
        
        // Process even small movements for smooth rotation
        if (abs(dx) == 0 && abs(dy) == 0)
            return (0);
        
        // Optimized scaling for smooth rotation without frame skipping
        float norm_dx = (float)dx * MOUSE_ROTATION_SENSITIVITY;
        float norm_dy = -(float)dy * MOUSE_ROTATION_SENSITIVITY;
        
        // Apply trackball rotation
        apply_trackball_rotation(data->camera, norm_dx, norm_dy);
        
        // Update last mouse position
        data->controls->last_mouse_x = x;
        data->controls->last_mouse_y = y;
        
        // Immediate redraw for smooth interaction
        draw_map(data);
    }
    return (0);
}