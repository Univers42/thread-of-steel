/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:04:38 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZATION_H
# define OPTIMIZATION_H

# include "fdf_internal.h"
# include "geometry.h"

/* ************************************************************************** */
/*                          LEVEL OF DETAIL (LOD) SYSTEM                     */
/* ************************************************************************** */

// LOD calculation and management
typedef enum e_lod_level
{
    LOD_FULL = 0,        // Render every point
    LOD_HALF = 1,        // Skip every other point
    LOD_QUARTER = 2,     // Skip 3 out of 4 points
    LOD_EIGHTH = 3,      // Skip 7 out of 8 points
    LOD_WIREFRAME = 4    // Only render outline
} t_lod_level;

t_lod_level calculate_lod_level(float zoom, int map_size);
int should_render_point(int x, int y, t_lod_level lod);
int calculate_adaptive_step(float zoom, int dimension);

/* ************************************************************************** */
/*                          FRUSTUM CULLING SYSTEM                           */
/* ************************************************************************** */

// View frustum for culling invisible geometry
typedef struct s_frustum
{
    float left, right, top, bottom, near, far;
    float planes[6][4];  // 6 planes, each with 4 coefficients (a,b,c,d)
} t_frustum;

void frustum_calculate(t_frustum *frustum, t_camera *camera, int width, int height);
int  frustum_point_inside(t_frustum *frustum, t_vec3 point);
int  frustum_line_intersects(t_frustum *frustum, t_vec3 p1, t_vec3 p2);

/* ************************************************************************** */
/*                          FAST BRESENHAM SYSTEM                            */
/* ************************************************************************** */

// Optimized line drawing
typedef struct s_bresenham_state
{
    int dx, dy;
    int sx, sy;
    int err, e2;
    int steep;
} t_bresenham_state;

void bresenham_init(t_bresenham_state *state, t_point p1, t_point p2);
int  bresenham_step(t_bresenham_state *state, int *x, int *y);
void draw_line_bresenham_fast(t_data *data, t_point p1, t_point p2);

/* ************************************************************************** */
/*                          MEMORY OPTIMIZATION                              */
/* ************************************************************************** */

// Efficient memory pooling for frequent allocations
typedef struct s_point_pool
{
    t_point *points;
    int     capacity;
    int     used;
    int     chunk_size;
} t_point_pool;

t_point_pool *point_pool_create(int initial_capacity);
t_point *point_pool_get(t_point_pool *pool);
void point_pool_reset(t_point_pool *pool);
void point_pool_destroy(t_point_pool *pool);

/* ************************************************************************** */
/*                          CACHE OPTIMIZATION                               */
/* ************************************************************************** */

// Cache frequently calculated values
typedef struct s_render_cache
{
    int     last_frame_hash;
    t_vec3  *transformed_points;
    int     *visibility_flags;
    int     cache_valid;
    int     point_count;
} t_render_cache;

int render_cache_check_valid(t_render_cache *cache, t_data *data);
void render_cache_invalidate(t_render_cache *cache);
void render_cache_update(t_render_cache *cache, t_data *data);

#endif
