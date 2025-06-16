/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:49:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 20:53:28 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int handle_keypress(int key, t_data *data)
{
    if (key == ESC_KEY)
        handle_close(data);
    else if (key == W_KEY || key == UP_KEY)
        data->camera->offset_y -= 20;
    else if (key == S_KEY || key == DOWN_KEY)
        data->camera->offset_y += 20;
    else if (key == A_KEY || key == LEFT_KEY)
        data->camera->offset_x -= 20;
    else if (key == D_KEY || key == RIGHT_KEY)
        data->camera->offset_x += 20;
    else if (key == Q_KEY)
        data->camera->angle_z -= 0.05;
    else if (key == E_KEY)
        data->camera->angle_z += 0.05;
    else if (key == R_KEY)
        data->camera->angle_x -= 0.05;
    else if (key == T_KEY)
        data->camera->angle_x += 0.05;
    else if (key == PLUS_KEY)
        data->camera->zoom *= 1.2;
    else if (key == MINUS_KEY)
        data->camera->zoom *= 0.8;
    else if (key == SPACE_KEY)
        data->controls->color_mode = (data->controls->color_mode + 1) % 3;
    // Add Z-scale controls for fine-tuning
    else if (key == 122) // 'z' key - increase Z scale
    {
        data->camera->z_scale += 0.2;
        if (data->camera->z_scale > 10)
            data->camera->z_scale = 10;
    }
    else if (key == 120) // 'x' key - decrease Z scale  
    {
        data->camera->z_scale -= 0.2;
        if (data->camera->z_scale < 0.1)
            data->camera->z_scale = 0.1;
    }
    // Reset camera to default position
    else if (key == 114) // 'r' key - reset camera
    {
        data->camera->angle_x = DEFAULT_ANGLE_X;
        data->camera->angle_y = DEFAULT_ANGLE_Y;
        data->camera->angle_z = DEFAULT_ANGLE_Z;
        data->camera->zoom = DEFAULT_ZOOM;
        data->camera->offset_x = WIN_WIDTH / 2;
        data->camera->offset_y = WIN_HEIGHT / 2;
        init_rotation_matrix(data->camera);  // Reset trackball quaternion and matrix
    }

    draw_map(data);
    return (0);
}