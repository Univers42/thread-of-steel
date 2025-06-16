/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:42:50 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include <math.h>

// Define M_PI if not defined by system
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Forward declaration to avoid circular dependency
struct s_data;

// Shape constants
# define NUM_SHAPES 9
# define SHAPE_FLAT 0
# define SHAPE_SPHERE 1
# define SHAPE_CYLINDER 2
# define SHAPE_CONE 3
# define SHAPE_WAVE 4
# define SHAPE_TORUS 5
# define SHAPE_SADDLE 6
# define SHAPE_HELIX 7
# define SHAPE_RIPPLE 8

// Alt key modifier mask
# define ALT_MASK 0x08

// Shape transformation parameters structure
typedef struct s_shape_params
{
    float norm_x;       // Normalized X coordinate (0.0 to 1.0)
    float norm_y;       // Normalized Y coordinate (0.0 to 1.0)
    int   map_width;    // Map width for calculations
    int   map_height;   // Map height for calculations
    float scale;        // Shape scale factor
    float offset;       // Shape offset
}   t_shape_params;

// Shape result structure
typedef struct s_shape_result
{
    float x;
    float y;
    float z;
}   t_shape_result;

// Shape function pointer type
typedef t_shape_result (*shape_func_t)(float x, float y, float z, t_shape_params params);

// Shape descriptor structure
typedef struct s_shape_info
{
    const char    *name;
    shape_func_t   transform;
    float          default_scale;
    float          default_offset;
}   t_shape_info;

// Individual shape transformation functions
t_shape_result shape_flat_transform(float x, float y, float z, t_shape_params params);
t_shape_result shape_sphere_transform(float x, float y, float z, t_shape_params params);
t_shape_result shape_cylinder_transform(float x, float y, float z, t_shape_params params);
t_shape_result shape_cone_transform(float x, float y, float z, t_shape_params params);
t_shape_result shape_wave_transform(float x, float y, float z, t_shape_params params);
t_shape_result shape_torus_transform(float x, float y, float z, t_shape_params params);
t_shape_result shape_saddle_transform(float x, float y, float z, t_shape_params params);
t_shape_result shape_helix_transform(float x, float y, float z, t_shape_params params);
t_shape_result shape_ripple_transform(float x, float y, float z, t_shape_params params);

// Shape control functions
int handle_shape_switch(int key, int modifier, struct s_data *data);
const char* get_shape_name(int shape);
void cycle_shape(struct s_data *data);
t_shape_info* get_shape_info(int shape);

#endif
