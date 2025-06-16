/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:55:53 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 20:53:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define TRACKBALLSIZE (1.2f)
#define RENORMCOUNT 97

// Vector math functions
void vzero(float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}

void vset(float *v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void vcopy(const float *v1, float *v2)
{
    int i;
    for (i = 0; i < 3; i++)
        v2[i] = v1[i];
}

void vcross(const float *v1, const float *v2, float *cross)
{
    float temp[3];

    temp[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    temp[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    temp[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    vcopy(temp, cross);
}

float vlength(const float *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void vscale(float *v, float div)
{
    v[0] *= div;
    v[1] *= div;
    v[2] *= div;
}

void vnormal(float *v)
{
    vscale(v, 1.0/vlength(v));
}

float vdot(const float *v1, const float *v2)
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void vadd(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] + src2[0];
    dst[1] = src1[1] + src2[1];
    dst[2] = src1[2] + src2[2];
}

void vsub(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] - src2[0];
    dst[1] = src1[1] - src2[1];
    dst[2] = src1[2] - src2[2];
}

// Trackball projection function
static float tb_project_to_sphere(float r, float x, float y)
{
    float d, t, z;

    d = sqrt(x*x + y*y);
    if (d < r * 0.70710678118654752440) {    /* Inside sphere */
        z = sqrt(r*r - d*d);
    } else {           /* On hyperbola */
        t = r / 1.41421356237309504880;
        z = t*t / d;
    }
    return z;
}

void axis_to_quat(float a[3], float phi, float q[4])
{
    vcopy(a, q);
    vnormal(q);
    vscale(q, sin(phi/2.0));
    q[3] = cos(phi/2.0);
}

void normalize_quat(float q[4])
{
    int i;
    float mag;

    mag = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    for (i = 0; i < 4; i++) q[i] /= mag;
}

void trackball(float q[4], float p1x, float p1y, float p2x, float p2y)
{
    float a[3]; /* Axis of rotation */
    float phi;  /* how much to rotate about axis */
    float p1[3], p2[3], d[3];
    float t;

    if (p1x == p2x && p1y == p2y) {
        /* Zero rotation */
        vzero(q);
        q[3] = 1.0;
        return;
    }

    /*
     * First, figure out z-coordinates for projection of P1 and P2 to
     * deformed sphere
     */
    vset(p1, p1x, p1y, tb_project_to_sphere(TRACKBALLSIZE, p1x, p1y));
    vset(p2, p2x, p2y, tb_project_to_sphere(TRACKBALLSIZE, p2x, p2y));

    /*
     *  Now, we want the cross product of P1 and P2
     */
    vcross(p2, p1, a);

    /*
     *  Figure out how much to rotate around that axis.
     */
    vsub(p1, p2, d);
    t = vlength(d) / (2.0*TRACKBALLSIZE);

    /*
     * Avoid problems with out-of-control values...
     */
    if (t > 1.0) t = 1.0;
    if (t < -1.0) t = -1.0;
    phi = 2.0 * asin(t);

    axis_to_quat(a, phi, q);
}

void add_quats(float q1[4], float q2[4], float dest[4])
{
    static int count = 0;
    float t1[4], t2[4], t3[4];
    float tf[4];

    vcopy(q1, t1);
    vscale(t1, q2[3]);

    vcopy(q2, t2);
    vscale(t2, q1[3]);

    vcross(q2, q1, t3);
    vadd(t1, t2, tf);
    vadd(t3, tf, tf);
    tf[3] = q1[3] * q2[3] - vdot(q1, q2);

    dest[0] = tf[0];
    dest[1] = tf[1];
    dest[2] = tf[2];
    dest[3] = tf[3];

    if (++count > RENORMCOUNT) {
        count = 0;
        normalize_quat(dest);
    }
}

void build_rotmatrix_3x3(float m[3][3], float q[4])
{
    m[0][0] = 1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]);
    m[0][1] = 2.0 * (q[0] * q[1] - q[2] * q[3]);
    m[0][2] = 2.0 * (q[2] * q[0] + q[1] * q[3]);

    m[1][0] = 2.0 * (q[0] * q[1] + q[2] * q[3]);
    m[1][1] = 1.0 - 2.0 * (q[2] * q[2] + q[0] * q[0]);
    m[1][2] = 2.0 * (q[1] * q[2] - q[0] * q[3]);

    m[2][0] = 2.0 * (q[2] * q[0] - q[1] * q[3]);
    m[2][1] = 2.0 * (q[1] * q[2] + q[0] * q[3]);
    m[2][2] = 1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]);
}

void init_rotation_matrix(t_camera *camera)
{
    // Initialize quaternion to identity (no rotation)
    vzero(camera->trackball_quat);
    camera->trackball_quat[3] = 1.0;
    
    vzero(camera->last_quat);
    camera->last_quat[3] = 1.0;
    
    // Build initial rotation matrix
    build_rotmatrix_3x3(camera->rotation_matrix, camera->trackball_quat);
}

void apply_trackball_rotation(t_camera *camera, float dx, float dy)
{
    float new_quat[4];
    
    // Skip extremely small movements only
    if (fabs(dx) < 0.0001 && fabs(dy) < 0.0001)
        return;
    
    // Smooth trackball coordinates
    float p1x = 0.0;
    float p1y = 0.0;
    float p2x = dx * 0.8;  // Balanced scaling for smooth control
    float p2y = dy * 0.8;  // Balanced scaling for smooth control
    
    // Calculate trackball rotation
    trackball(new_quat, p1x, p1y, p2x, p2y);
    
    // Add to current rotation
    add_quats(new_quat, camera->trackball_quat, camera->trackball_quat);
    
    // Build rotation matrix from quaternion
    build_rotmatrix_3x3(camera->rotation_matrix, camera->trackball_quat);
}

static void rotate_point_matrix(float *x, float *y, float *z, t_camera *camera)
{
    float new_x = camera->rotation_matrix[0][0] * (*x) + 
                  camera->rotation_matrix[0][1] * (*y) + 
                  camera->rotation_matrix[0][2] * (*z);
    float new_y = camera->rotation_matrix[1][0] * (*x) + 
                  camera->rotation_matrix[1][1] * (*y) + 
                  camera->rotation_matrix[1][2] * (*z);
    float new_z = camera->rotation_matrix[2][0] * (*x) + 
                  camera->rotation_matrix[2][1] * (*y) + 
                  camera->rotation_matrix[2][2] * (*z);
    
    *x = new_x;
    *y = new_y;
    *z = new_z;
}

// Add cached trigonometry for performance
static float cached_cos_x = 0, cached_sin_x = 0;
static float cached_cos_y = 0, cached_sin_y = 0;
static float cached_cos_z = 0, cached_sin_z = 0;
static float last_angle_x = -999, last_angle_y = -999, last_angle_z = -999;

t_point project_point(t_point point, t_camera *camera)
{
    t_point projected;
    float x, y, z;

    // Cache trigonometric calculations
    if (camera->angle_x != last_angle_x)
    {
        cached_cos_x = cos(camera->angle_x);
        cached_sin_x = sin(camera->angle_x);
        last_angle_x = camera->angle_x;
    }
    if (camera->angle_y != last_angle_y)
    {
        cached_cos_y = cos(camera->angle_y);
        cached_sin_y = sin(camera->angle_y);
        last_angle_y = camera->angle_y;
    }
    if (camera->angle_z != last_angle_z)
    {
        cached_cos_z = cos(camera->angle_z);
        cached_sin_z = sin(camera->angle_z);
        last_angle_z = camera->angle_z;
    }

    // Convert to float and apply minimal Z scaling to preserve proportions
    x = (float)point.x;
    y = (float)point.y;
    z = (float)point.z;

    // Apply matrix rotation instead of Euler angles
    rotate_point_matrix(&x, &y, &z, camera);

    // Apply isometric projection with proper scaling
    projected.x = (int)((x - y) * cos(0.523599) * camera->zoom) + camera->offset_x;
    projected.y = (int)((x + y) * sin(0.523599) * camera->zoom - z * camera->zoom * 0.5) + camera->offset_y;
    
    projected.z = (int)z;
    projected.color = point.color;
    return (projected);
}