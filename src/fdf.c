/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:36:56 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 12:45:53 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <math.h>

int main(int argc, char **argv)
{
    t_data data;
    t_camera *camera;
    t_controls *controls;
    
    if (argc != 2)
    {
        ft_putendl_fd("Usage: ./fdf map_file", 2);
        return (1);
    }
    
    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);
    
    data.map = parse_map(argv[1]);
    if (!data.map)
    {
        mlx_destroy_display(data.mlx);
        free(data.mlx);
        return (1);
    }
    
    // Debug: Print some color information from the parsed map
    ft_putendl_fd("=== MAP COLOR DEBUG ===", 1);
    int colored_points = 0;
    for (int y = 0; y < data.map->height && y < 5; y++) // Check first 5 rows
    {
        for (int x = 0; x < data.map->width && x < 10; x++) // Check first 10 cols
        {
            if (data.map->points[y][x].color != 0xFFFFFF)
            {
                ft_putstr_fd("Found colored point at (", 1);
                ft_putnbr_fd(x, 1);
                ft_putstr_fd(",", 1);
                ft_putnbr_fd(y, 1);
                ft_putstr_fd(") with color 0xFF0000", 1);
                ft_putendl_fd("", 1);
                colored_points++;
            }
        }
    }
    if (colored_points == 0)
        ft_putendl_fd("No colored points found in sample area", 1);
    else
    {
        ft_putstr_fd("Found ", 1);
        ft_putnbr_fd(colored_points, 1);
        ft_putendl_fd(" colored points", 1);
    }
    
    camera = malloc(sizeof(t_camera));
    controls = malloc(sizeof(t_controls));
    if (!camera || !controls)
    {
        free_map(data.map);
        mlx_destroy_display(data.mlx);
        free(data.mlx);
        if (camera) free(camera);
        if (controls) free(controls);
        return (1);
    }
    
    // Initialize camera with better defaults
    camera->zoom = DEFAULT_ZOOM;
    camera->angle_x = DEFAULT_ANGLE_X;
    camera->angle_y = DEFAULT_ANGLE_Y; 
    camera->angle_z = DEFAULT_ANGLE_Z;
    camera->last_frame_hash = 0;  // Initialize frame hash
    
    // Initialize rotation matrix
    init_rotation_matrix(camera);
    
    // Calculate appropriate Z-scale based on map size and Z-range
    int z_range = data.map->max_z - data.map->min_z;
    int map_size = (data.map->width > data.map->height) ? data.map->width : data.map->height;
    
    if (z_range > 0)
        camera->z_scale = map_size / (z_range * 2); // Scale Z relative to map dimensions
    else
        camera->z_scale = 1;
    
    // Ensure minimum visibility
    if (camera->z_scale < 1)
        camera->z_scale = 1;
    if (camera->z_scale > 3)
        camera->z_scale = 3;
    
    // Center the map properly based on map dimensions
    camera->offset_x = WIN_WIDTH / 2;
    camera->offset_y = WIN_HEIGHT / 2;
    camera->projection = 0;
    
    // Initialize controls
    controls->mouse_x = 0;
    controls->mouse_y = 0;
    controls->mouse_pressed = 0;
    controls->color_mode = 0;           // Start with white default mode
    controls->color_theme = 0;          // Start with no theme (shows embedded colors)
    controls->shape_mode = 0;           // Initialize with flat shape
    controls->alt_pressed = 0;          // Initialize Alt key state
    controls->last_mouse_x = 0;
    controls->last_mouse_y = 0;
    
    data.camera = camera;
    data.controls = controls;
    
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF - Interactive Wireframe");
    data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, 
                                  &data.line_length, &data.endian);
    
    // Initial draw
    draw_map(&data);
    
    // Set up event handlers with proper masks for smooth interaction
    mlx_hook(data.win, 2, 1L<<0, handle_keypress, &data);
    mlx_hook(data.win, 3, 1L<<1, handle_keyrelease, &data);  // Add key release handler
    mlx_hook(data.win, 4, 1L<<2, handle_mouse_press, &data);
    mlx_hook(data.win, 5, 1L<<3, handle_mouse_release, &data);
    mlx_hook(data.win, 6, 1L<<6, handle_mouse_move, &data);
    mlx_hook(data.win, 17, 1L<<17, handle_close, &data);
    
    // Enable key repeat for smooth movement
    mlx_do_key_autorepeatoff(data.mlx);
    
    // Print controls
    ft_putendl_fd("=== FDF CONTROLS ===", 1);
    ft_putendl_fd("WASD/Arrow Keys: Move", 1);
    ft_putendl_fd("Mouse drag: Rotate", 1);
    ft_putendl_fd("Q/E: Rotate Z-axis", 1);
    ft_putendl_fd("R/T: Rotate X-axis", 1);
    ft_putendl_fd("+/-: Zoom", 1);
    ft_putendl_fd("Mouse wheel: Zoom", 1);
    ft_putendl_fd("0: Show embedded colors (default white)", 1);  // Add this line
    ft_putendl_fd("1-9: Color themes", 1);
    ft_putendl_fd("Alt+1-9: Shape transforms", 1);
    ft_putendl_fd("Tab: Cycle themes", 1);
    ft_putendl_fd("Alt+Tab: Cycle shapes", 1);
    ft_putendl_fd("Space: Change colors", 1);
    ft_putendl_fd("ESC: Exit", 1);
    
    mlx_loop(data.mlx);
    return (0);
}