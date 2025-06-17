/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:37:12 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:08:40 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "fdf_internal.h"
# include "geometry.h"

/* ************************************************************************** */
/*                          FDF PROJECT UTILITY LIBRARY                      */
/* ************************************************************************** */

/* ************************************************************************** */
/*                          MATHEMATICAL UTILITIES                           */
/* ************************************************************************** */

// Fast math helpers for shape calculations
static inline float	fast_sin(float x) { return (sinf(x)); }
static inline float	fast_cos(float x) { return (cosf(x)); }
static inline float	fast_sqrt(float x) { return (sqrtf(x)); }

// Distance and interpolation helpers
float		point_distance_2d(t_vec2 coord1, t_vec2 coord2);
float		smooth_step(float edge0, float edge1, float x);
float		lerp(float a, float b, float t);

/* ************************************************************************** */
/*                          COORDINATE SYSTEM UTILITIES                      */
/* ************************************************************************** */

// Coordinate conversion utilities (complete set)
t_spherical		cartesian_to_spherical(t_vec3 point);
t_vec3			spherical_to_cartesian(t_spherical sph);
t_cylindrical	cartesian_to_cylindrical(t_vec3 point);
t_vec3			cylindrical_to_cartesian(t_cylindrical cyl);
void			map_to_polar_coords(t_vec2 norm, t_map *map_info);

// Coordinate system utilities
t_spherical		spherical_lerp(t_spherical a, t_spherical b, float t);
t_polar			polar_from_normalized(t_vec2 norm, float max_radius);
t_spherical		spherical_add(t_spherical a, t_spherical b);

/* ************************************************************************** */
/*                          VECTOR MATHEMATICS                               */
/* ************************************************************************** */

// 3D vector operations (complete set)
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, float scale);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
float	vec3_dot(t_vec3 a, t_vec3 b);
float	vec3_length(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);

// 2D vector operations (complete set)
t_vec2	vec2_add(t_vec2 a, t_vec2 b);
t_vec2	vec2_subtract(t_vec2 a, t_vec2 b);
t_vec2	vec2_scale(t_vec2 v, float scale);
float	vec2_dot(t_vec2 a, t_vec2 b);
float	vec2_length(t_vec2 v);
t_vec2	vec2_normalize(t_vec2 v);

/* ************************************************************************** */
/*                          MATRIX OPERATIONS                                */
/* ************************************************************************** */

// Matrix transformation functions (pure math)
void	matrix_multiply_3x3(float a[3][3], float b[3][3], float result[3][3]);
void	matrix_vector_multiply_3x3(float matrix[3][3], t_vec3 vec, t_vec3 *result);
void	matrix_identity_3x3(float matrix[3][3]);

/* ************************************************************************** */
/*                          SHAPE MANAGEMENT UTILITIES                       */
/* ************************************************************************** */

// Shape management and control
const char		*get_shape_name(t_shape_type shape);
const char		*get_shape_description(t_shape_type shape);
t_shape_info	*get_shape_info(t_shape_type shape);

/* ************************************************************************** */
/*                          PERFORMANCE UTILITIES                            */
/* ************************************************************************** */

// Performance utilities
int		calculate_shape_lod(float zoom, t_shape_type shape);
int		is_point_visible(t_point point, int width, int height);

// Memory and cleanup utilities
void	cleanup_shape_resources(void);
void	init_shape_system(void);

/* ************************************************************************** */
/*                          FDF-SPECIFIC HELPERS                             */
/* ************************************************************************** */

// Color utilities
int		interpolate_color(int color1, int color2, float t);
int		get_gradient_color(float value, float min_val, float max_val, int color1, int color2);

// Map utilities
void	calculate_map_bounds(t_map *map);
t_vec2	get_map_center(t_map *map);
float	get_map_scale_factor(t_map *map, int window_width, int window_height);

// Projection utilities
t_point	isometric_project(t_vec3 point);
t_point	perspective_project(t_vec3 point, float fov, float aspect);

#endif