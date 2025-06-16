/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_themes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:15:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:24:17 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Fast interpolation using bit shifts
static int fast_interpolate(int c1, int c2, int ratio_256)
{
    int inv_ratio = 256 - ratio_256;
    int r = ((((c1 >> 16) & 0xFF) * inv_ratio + ((c2 >> 16) & 0xFF) * ratio_256) >> 8);
    int g = ((((c1 >> 8) & 0xFF) * inv_ratio + ((c2 >> 8) & 0xFF) * ratio_256) >> 8);
    int b = (((c1 & 0xFF) * inv_ratio + (c2 & 0xFF) * ratio_256) >> 8);
    return (r << 16) | (g << 8) | b;
}

// Initialize lookup table with gradient colors
static void init_gradient_lut(int *lut, int *colors, int num_colors)
{
    int i;
    int segment;
    int local_ratio;
    
    for (i = 0; i < 256; i++) {
        segment = (i * (num_colors - 1)) >> 8;
        local_ratio = ((i * (num_colors - 1)) & 0xFF);
        if (segment >= num_colors - 1) {
            lut[i] = colors[num_colors - 1];
        } else {
            lut[i] = fast_interpolate(colors[segment], colors[segment + 1], local_ratio);
        }
    }
}

// Get color from theme using lookup tables
static int get_theme_color_from_lut(int theme, int index)
{
    static int earth_lut[256];
    static int fire_lut[256];
    static int ocean_lut[256];
    static int rainbow_lut[256];
    static int mono_lut[256];
    static int sunset_lut[256];
    static int arctic_lut[256];
    static int neon_lut[256];
    static int desert_lut[256];
    static int initialized = 0;
    
    if (!initialized) {
        // Earth theme colors
        int earth_colors[] = {0x000080, 0x0066CC, 0x66B2FF, 0xFFE066, 0x66CC00, 
                             0x009900, 0x663300, 0x996633, 0xCCCCCC, 0xFFFFFF};
        init_gradient_lut(earth_lut, earth_colors, 10);
        
        // Fire theme colors
        int fire_colors[] = {0x000000, 0x330000, 0x990000, 0xFF3300, 0xFF9900, 
                            0xFFCC00, 0xFFFF00, 0xFFFFCC, 0xFFFFFF};
        init_gradient_lut(fire_lut, fire_colors, 9);
        
        // Ocean theme colors
        int ocean_colors[] = {0x000033, 0x000066, 0x003399, 0x0066CC, 0x3399FF, 
                             0x66CCFF, 0x99DDFF, 0xCCEEFF, 0xFFFFFF};
        init_gradient_lut(ocean_lut, ocean_colors, 9);
        
        // Rainbow theme - simple HSV to RGB conversion
        int i;
        for (i = 0; i < 256; i++) {
            int hue = (i * 360) >> 8;
            int h = hue / 60;
            int f_val = ((hue % 60) * 255) / 60;
            int p = 0;
            int q = 255 - f_val;
            int t = f_val;
            int r, g, b;
            
            if (h == 0) { r = 255; g = t; b = p; }
            else if (h == 1) { r = q; g = 255; b = p; }
            else if (h == 2) { r = p; g = 255; b = t; }
            else if (h == 3) { r = p; g = q; b = 255; }
            else if (h == 4) { r = t; g = p; b = 255; }
            else { r = 255; g = p; b = q; }
            
            rainbow_lut[i] = (r << 16) | (g << 8) | b;
        }
        
        // Monochrome theme
        for (i = 0; i < 256; i++) {
            mono_lut[i] = (i << 16) | (i << 8) | i;
        }
        
        // Sunset theme colors
        int sunset_colors[] = {0x1a0033, 0x330066, 0x660099, 0x9900CC, 0xCC00FF, 
                              0xFF3399, 0xFF6666, 0xFF9933, 0xFFCC00, 0xFFFF99};
        init_gradient_lut(sunset_lut, sunset_colors, 10);
        
        // Arctic theme colors
        int arctic_colors[] = {0x003366, 0x006699, 0x0099CC, 0x33CCFF, 0x66DDFF, 
                              0x99EEFF, 0xCCF7FF, 0xE6FBFF, 0xFFFFFF};
        init_gradient_lut(arctic_lut, arctic_colors, 9);
        
        // Neon theme colors
        int neon_colors[] = {0x000000, 0x330066, 0x6600CC, 0x9933FF, 0xCC66FF, 
                            0xFF00FF, 0xFF3399, 0xFF6666, 0x00FFFF, 0x66FFFF};
        init_gradient_lut(neon_lut, neon_colors, 10);
        
        // Desert theme colors
        int desert_colors[] = {0x3D2914, 0x8B4513, 0xA0522D, 0xCD853F, 0xDAA520, 
                              0xF4A460, 0xFFE4B5, 0xFFF8DC, 0xFFFFE0};
        init_gradient_lut(desert_lut, desert_colors, 9);
        
        initialized = 1;
    }
    
    // Clamp index to valid range
    if (index < 0) index = 0;
    if (index > 255) index = 255;
    
    // Return color from appropriate lookup table
    if (theme == 1) return earth_lut[index];
    else if (theme == 2) return fire_lut[index];
    else if (theme == 3) return ocean_lut[index];
    else if (theme == 4) return rainbow_lut[index];
    else if (theme == 5) return mono_lut[index];
    else if (theme == 6) return sunset_lut[index];
    else if (theme == 7) return arctic_lut[index];
    else if (theme == 8) return neon_lut[index];
    else if (theme == 9) return desert_lut[index];
    else return 0xFFFFFF; // Default white
}

// Ultra-fast themed color function
int get_themed_color(int z_value, int min_z, int max_z, int theme)
{
    int range = max_z - min_z;
    int index;
    
    if (range == 0) return get_theme_color_from_lut(theme, 128);
    
    // Fast height ratio calculation using bit operations
    int clamped_z = z_value - min_z;
    if (clamped_z < 0) clamped_z = 0;
    if (clamped_z > range) clamped_z = range;
    
    // Fast multiplication and division using bit shifts where possible
    index = (clamped_z << 8) / range;  // Equivalent to (clamped_z * 256) / range
    if (index > 255) index = 255;
    
    return get_theme_color_from_lut(theme & 0x0F, index);
}

const char* get_theme_name(int theme)
{
    static const char* theme_names[10] = {
        "Default",
        "Earth/Terrain",
        "Fire/Heat", 
        "Ocean Depth",
        "Rainbow",
        "Monochrome",
        "Sunset",
        "Arctic",
        "Neon",
        "Desert/Mars"
    };
    
    return theme_names[theme & 0x0F];  // Bitwise AND for bounds checking
}
