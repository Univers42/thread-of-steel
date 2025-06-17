/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theme_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:50:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int handle_theme_switch(int key, t_data *data)
{
    static t_color_theme key_theme_map[256];
    static int map_initialized = 0;
    t_color_theme new_theme;
    
    if (!map_initialized) {
        // Initialize all to invalid theme
        for (int i = 0; i < 256; i++)
            key_theme_map[i] = NUM_THEMES; // Invalid theme
        
        // Map number keys to themes
        key_theme_map[48] = THEME_DEFAULT;  // '0' key -> Default/Embedded colors
        key_theme_map[49] = THEME_EARTH;    // '1' key -> Earth theme
        key_theme_map[50] = THEME_FIRE;     // '2' key -> Fire theme
        key_theme_map[51] = THEME_OCEAN;    // '3' key -> Ocean theme
        key_theme_map[52] = THEME_RAINBOW;  // '4' key -> Rainbow theme
        key_theme_map[53] = THEME_MONO;     // '5' key -> Monochrome theme
        key_theme_map[54] = THEME_SUNSET;   // '6' key -> Sunset theme
        key_theme_map[55] = THEME_ARCTIC;   // '7' key -> Arctic theme
        key_theme_map[56] = THEME_NEON;     // '8' key -> Neon theme
        key_theme_map[57] = THEME_DESERT;   // '9' key -> Desert theme
        map_initialized = 1;
    }
    
    // Check if key is in valid range
    if (key < 48 || key > 57)
        return (0);
    
    new_theme = key_theme_map[key];
    
    if (new_theme < NUM_THEMES)
    {
        data->controls->color_theme = new_theme;
        data->controls->color_mode = 0;  // Reset color_mode when using themes
        
        if (new_theme == THEME_DEFAULT)
            ft_putendl_fd("Color mode: Embedded colors (white default)", 1);
        else
        {
            ft_putstr_fd("Color theme changed to: ", 1);
            ft_putendl_fd((char*)get_theme_name(new_theme), 1);
        }
        
        draw_map(data);
        return (1);
    }
    
    return (0);
}

void cycle_color_theme(t_data *data)
{
    data->controls->color_theme = (data->controls->color_theme + 1) % NUM_THEMES;
    
    if (data->controls->color_theme == THEME_DEFAULT)
        ft_putendl_fd("Color mode: Embedded colors (white default)", 1);
    else
    {
        ft_putstr_fd("Color theme: ", 1);
        ft_putendl_fd((char*)get_theme_name(data->controls->color_theme), 1);
    }
    
    draw_map(data);
}