/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theme_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 11:01:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Ultra-fast theme switching using lookup table
int handle_theme_switch(int key, t_data *data)
{
    static int key_theme_map[256] = {0}; // Initialize all to 0
    static int map_initialized = 0;
    int new_theme;
    
    if (!map_initialized) {
        // Map number keys to themes
        key_theme_map[48] = 0;  // '0' key -> Embedded colors mode (white default)
        key_theme_map[49] = 1;  // '1' key -> Earth theme
        key_theme_map[50] = 2;  // '2' key -> Fire theme
        key_theme_map[51] = 3;  // '3' key -> Ocean theme
        key_theme_map[52] = 4;  // '4' key -> Rainbow theme
        key_theme_map[53] = 5;  // '5' key -> Monochrome theme
        key_theme_map[54] = 6;  // '6' key -> Sunset theme
        key_theme_map[55] = 7;  // '7' key -> Arctic theme
        key_theme_map[56] = 8;  // '8' key -> Neon theme
        key_theme_map[57] = 9;  // '9' key -> Desert theme
        map_initialized = 1;
    }
    
    // Handle '0' key specially for embedded colors
    if (key == 48) // '0' key
    {
        data->controls->color_theme = 0;
        data->controls->color_mode = 0;  // Also reset color_mode to ensure white default
        ft_putendl_fd("Color mode: Embedded colors (white default)", 1);
        draw_map(data);
        return (1);
    }
    
    // Bounds check using bitwise AND
    new_theme = key_theme_map[key & 0xFF];
    
    if (new_theme > 0)
    {
        data->controls->color_theme = new_theme;
        data->controls->color_mode = 0;  // Reset color_mode when using themes
        
        // Print theme change notification
        ft_putstr_fd("Color theme changed to: ", 1);
        ft_putendl_fd((char*)get_theme_name(new_theme), 1);
        
        // Redraw with new theme
        draw_map(data);
        return (1); // Key handled
    }
    
    return (0); // Key not handled
}

// Cycle through themes with Tab key
void cycle_color_theme(t_data *data)
{
    data->controls->color_theme++;
    // Use bitwise operations for modulo (faster than %)
    if (data->controls->color_theme > 9)
        data->controls->color_theme = 0;  // Include embedded colors mode in cycle
    
    if (data->controls->color_theme == 0)
        ft_putendl_fd("Color mode: Embedded colors (white default)", 1);
    else
    {
        ft_putstr_fd("Color theme: ", 1);
        ft_putendl_fd((char*)get_theme_name(data->controls->color_theme), 1);
    }
    
    draw_map(data);
}