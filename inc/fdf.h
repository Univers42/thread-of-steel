/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:27:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:57:44 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "Minilibx/mlx.h"
# include "shapes.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

// Define mathematical constants if not available
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Window dimensions
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

// Default camera settings
# define DEFAULT_ZOOM 20
# define DEFAULT_Z_SCALE 1
# define DEFAULT_ANGLE_X -0.5
# define DEFAULT_ANGLE_Y 0.0
# define DEFAULT_ANGLE_Z 0.5

// Mouse sensitivity
# define MOUSE_ROTATION_SENSITIVITY 0.003
# define MOUSE_ZOOM_SENSITIVITY 1.1

// Key codes
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define Q_KEY 113
# define E_KEY 101
# define R_KEY 114
# define T_KEY 116
# define UP_KEY 65362
# define DOWN_KEY 65364
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define PLUS_KEY 61
# define MINUS_KEY 45
# define SPACE_KEY 32
# define TAB_KEY 65289
# define ALT_L 65513        // Add Alt key codes
# define ALT_R 65514

// Mouse buttons
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

typedef struct s_point
{
    int x;
    int y;
    int z;
    int color;
}   t_point;

typedef struct s_map
{
    t_point **points;
    int width;
    int height;
    int max_z;
    int min_z;
}   t_map;

typedef struct s_camera
{
    float zoom;
    float angle_x;
    float angle_y;
    float angle_z;
    int offset_x;
    int offset_y;
    int projection;
    int z_scale;
    float rotation_matrix[3][3];
    float trackball_quat[4];
    float last_quat[4];
    int last_frame_hash;  // Add frame hash for conditional rendering
}   t_camera;

typedef struct s_controls
{
    int mouse_x;
    int mouse_y;
    int mouse_pressed;
    int color_mode;
    int color_theme;
    int shape_mode;         // Add shape mode field
    int alt_pressed;        // Add Alt key state
    int last_mouse_x;
    int last_mouse_y;
}   t_controls;

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;          // MLX image pointer (MANDATORY)
    char *addr;         // Image buffer address (MANDATORY)
    int bits_per_pixel; // Bits per pixel (MANDATORY)
    int line_length;    // Line length in bytes (MANDATORY)
    int endian;         // Endian (MANDATORY)
    t_map *map;
    t_camera *camera;
    t_controls *controls;
}   t_data;

// Function prototypes
t_map *parse_map(char *filename);
t_point *parse_line(char *line, int y, int width);
void draw_map(t_data *data);
void draw_line(t_data *data, t_point *p1, t_point *p2);
void free_map(t_map *map);
int handle_keypress(int key, t_data *data);
int handle_keyrelease(int key, t_data *data);    // Add missing declaration
int handle_mouse_press(int button, int x, int y, t_data *data);
int handle_mouse_release(int button, int x, int y, t_data *data);
int handle_mouse_move(int x, int y, t_data *data);
int handle_close(void *param);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_point project_point(t_point point, t_camera *camera);
int get_color(t_point p1, t_point p2, t_data *data);
void init_rotation_matrix(t_camera *camera);
void apply_trackball_rotation(t_camera *camera, float dx, float dy);
void multiply_matrices(float result[3][3], float a[3][3], float b[3][3]);
void trackball(float q[4], float p1x, float p1y, float p2x, float p2y);
void add_quats(float q1[4], float q2[4], float dest[4]);
void build_rotmatrix_3x3(float m[3][3], float q[4]);
void axis_to_quat(float a[3], float phi, float q[4]);
void normalize_quat(float q[4]);
float vlength(const float *v);
void vcross(const float *v1, const float *v2, float *cross);
void vcopy(const float *v1, float *v2);
void vset(float *v, float x, float y, float z);
void vzero(float *v);

// Add performance optimization function prototypes
void draw_map_optimized(t_data *data);
int calculate_lod(float zoom);
int is_line_visible(t_point p1, t_point p2, int width, int height);
void draw_line_fast(t_data *data, t_point *p1, t_point *p2);
int calculate_view_hash(t_data *data);
int clip_line(t_point *p1, t_point *p2, int width, int height);

// Add new function prototypes for color themes
int get_themed_color(int z_value, int min_z, int max_z, int theme);
const char* get_theme_name(int theme);
int handle_theme_switch(int key, t_data *data);
void cycle_color_theme(t_data *data);

// Add new function prototypes for shapes
t_point apply_shape_transform(t_point point, t_data *data);

#endif
