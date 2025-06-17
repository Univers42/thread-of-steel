/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:04:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOTION_H
# define MOTION_H

# include "fdf_internal.h"
# include "geometry.h"

/* ************************************************************************** */
/*                          TRACKBALL ROTATION SYSTEM                        */
/* ************************************************************************** */

// Trackball-specific structures
typedef struct s_trackball_state
{
    float current_quat[4];
    float last_quat[4];
    float rotation_matrix[3][3];
    int   mouse_down;
    int   last_x;
    int   last_y;
} t_trackball_state;

// Core trackball functions
void trackball_init(t_trackball_state *tb);
void trackball_start_rotation(t_trackball_state *tb, int x, int y);
void trackball_update_rotation(t_trackball_state *tb, int x, int y);
void trackball_end_rotation(t_trackball_state *tb);
void trackball_apply_to_camera(t_trackball_state *tb, t_camera *camera);

// Low-level trackball math
void trackball_project_to_sphere(float r, float x, float y, float *z);
void trackball_calc_rotation(float p1x, float p1y, float p2x, float p2y, float q[4]);

/* ************************************************************************** */
/*                          CAMERA MOTION SYSTEM                             */
/* ************************************************************************** */

// Camera motion control
void camera_start_pan(t_camera *camera, int x, int y);
void camera_update_pan(t_camera *camera, int x, int y, int dx, int dy);
void camera_zoom(t_camera *camera, float factor);
void camera_snap_to_angle(t_camera *camera, float angle_x, float angle_y, float angle_z);

// Motion interpolation for smooth animations
typedef struct s_motion_interpolator
{
    float start_value;
    float target_value;
    float current_value;
    float duration;
    float elapsed;
    int   active;
} t_motion_interpolator;

void motion_interpolator_start(t_motion_interpolator *interp, float start, float target, float duration);
int  motion_interpolator_update(t_motion_interpolator *interp, float delta_time);

/* ************************************************************************** */
/*                          SHAPE MORPHING SYSTEM                            */
/* ************************************************************************** */

// Shape morphing between different transformations
typedef struct s_shape_morph
{
    t_shape_type from_shape;
    t_shape_type to_shape;
    float        progress;        // 0.0 to 1.0
    float        duration;
    int          active;
} t_shape_morph;

void shape_morph_start(t_shape_morph *morph, t_shape_type from, t_shape_type to, float duration);
int  shape_morph_update(t_shape_morph *morph, float delta_time);
t_vec3 shape_morph_interpolate(t_point point, t_shape_context context, t_shape_morph *morph);

/* ************************************************************************** */
/*                          MOTION EVENT HANDLERS                            */
/* ************************************************************************** */

// High-level motion control functions
int handle_shape_switch(int key, int modifier, t_data *data);
void cycle_shape(t_data *data);
int handle_mouse_motion(int x, int y, t_data *data);
int handle_mouse_rotation(int button, int x, int y, t_data *data);

#endif
