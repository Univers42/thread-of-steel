/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:37:05 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:12:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
#define GEOMETRY_H

# include "fdf_internal.h"
# include <math.h>

// Forward declaration to avoid circular dependency
typedef struct s_data	t_data;
typedef struct s_point t_point;
typedef struct s_map	t_map;
/* ************************************************************************** */
/*                          UNIFIED GEOMETRY SYSTEM                          */
/* ************************************************************************** */

// Universal floating-point vector for all geometric calculations
typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;

// 2D vector for when z is not needed (replaces t_normalized_coords)
typedef struct s_vec2
{
	float x;
	float y;
} t_vec2;

// Spherical coordinates structure (r, theta, phi always together)
typedef struct s_spherical
{
	float r;        // radius (distance from origin)
	float theta;    // azimuthal angle (longitude, angle in xy-plane from x-axis)
	float phi;      // polar angle (colatitude, angle from positive z-axis)
} t_spherical;

// Cylindrical coordinates structure (for cylinder shape)
typedef struct s_cylindrical
{
	float rho;      // radial distance from z-axis
	float phi;      // azimuthal angle
	float z;        // height
} t_cylindrical;

// Polar coordinates structure (for 2D projections)
typedef struct s_polar
{
	float r;        // radius
	float theta;    // angle
} t_polar;

// Shape context remains the same but cleaner
typedef struct s_shape_context
{
	int   map_width;     // Map dimensions for normalization
	int   map_height;    
	float scale;         // User-adjustable scale factor
	float offset;        // User-adjustable offset
	float time;          // For animated shapes (future)
} t_shape_context;

// Function pointer type using unified vector system
typedef t_vec3 (*shape_func_t)(t_point point, t_shape_context context);

// Shape descriptor with metadata
typedef struct s_shape_info
{
	const char       *name;
	const char       *description;      // For UI/help
	shape_func_t      transform;
	float             default_scale;
	float             default_offset;
	int               requires_time;    // For animated shapes
} t_shape_info;

/* ************************************************************************** */
/*                          SHAPE TRANSFORMATION FUNCTIONS                   */
/* ************************************************************************** */

// Individual shape transformation functions with unified interface
t_vec3 shape_flat_transform(t_point point, t_shape_context context);
t_vec3 shape_sphere_transform(t_point point, t_shape_context context);
t_vec3 shape_cylinder_transform(t_point point, t_shape_context context);
t_vec3 shape_cone_transform(t_point point, t_shape_context context);
t_vec3 shape_wave_transform(t_point point, t_shape_context context);
t_vec3 shape_torus_transform(t_point point, t_shape_context context);
t_vec3 shape_saddle_transform(t_point point, t_shape_context context);
t_vec3 shape_helix_transform(t_point point, t_shape_context context);
t_vec3 shape_ripple_transform(t_point point, t_shape_context context);

// Main shape application function
t_point apply_shape_transform(t_point point, t_data *data);

#endif