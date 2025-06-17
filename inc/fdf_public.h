#ifndef FDF_PUBLIC_H
# define FDF_PUBLIC_H

# include "fdf_config.h"
# include "fdf_internal.h"
# include "libft/libft.h"
# include "Minilibx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

/* ************************************************************************** */
/*                          COLOR SYSTEM DATA STRUCTURES                     */
/* ************************************************************************** */

// RGB color structure with individual components (for processing)
typedef struct s_color_float
{
	float	r;        // Red component (0.0-1.0)
	float	g;        // Green component (0.0-1.0)
	float	b;        // Blue component (0.0-1.0)
	float	alpha;    // Alpha/transparency (0.0-1.0)
} t_color_float;

// RGB color structure with individual components (for final output)
typedef struct s_color
{
	int	r;        // Red component (0-255)
	int	g;        // Green component (0-255)
	int	b;        // Blue component (0-255)
	int	alpha;    // Alpha/transparency (0-255)
} t_color;

// HSV (Hue, Saturation, Value) color structure
typedef struct s_hue
{
	float	hue;         // Hue angle (0-360 degrees)
	float	saturation;  // Saturation (0.0-1.0)
	float	value;       // Value/brightness (0.0-1.0)
	float	alpha;       // Alpha/transparency (0.0-1.0)
} t_hue;

// Color adjustments and effects
typedef struct s_color_properties
{
	float	contrast;    // Contrast multiplier (0.5-2.0)
	float	brightness;  // Brightness adjustment (-1.0 to 1.0)
	float	saturation;  // Saturation multiplier (0.0-2.0)
	float	gamma;       // Gamma correction (0.5-3.0)
	float	exposure;    // HDR exposure (-3.0 to 3.0)
	int		invert;      // Invert colors (0 or 1)
} t_color_properties;

// Gradient definition with multiple stops
typedef struct s_gradient_stop
{
	float	position;    // Position in gradient (0.0-1.0)
	t_color	color;       // Color at this position
} t_gradient_stop;

typedef struct s_gradient
{
	t_gradient_stop	*stops;      // Array of gradient stops
	int				num_stops;   // Number of stops
	int				smooth;      // Smooth interpolation flag
} t_gradient;

// Complete color theme definition using new structures
typedef struct s_advanced_theme
{
	const char			*name;
	const char			*description;
	t_color				background;
	t_color				foreground;
	t_color				accent;
	t_gradient			height_gradient;
	t_color_properties	properties;
	int					use_hue_shift;
	float				hue_shift_speed;
} t_advanced_theme;

/* ************************************************************************** */
/*                          EXISTING DATA STRUCTURES                         */
/* ************************************************************************** */

// Keep t_point as integer-based for MLX rendering compatibility
typedef struct s_point {
	int x;
	int y;
	int z;
	int color;
} t_point;

typedef struct s_map {
	t_point **points;
	int width;
	int height;
	int max_z;
	int min_z;
	int	lat;
	int lon;
} t_map;

typedef struct s_camera {
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
	int last_frame_hash;
} t_camera;

typedef struct s_controls {
	int mouse_x;
	int mouse_y;
	int mouse_pressed;
	int color_mode;
	t_color_theme color_theme;
	t_shape_type shape_mode;
	int alt_pressed;
	int last_mouse_x;
	int last_mouse_y;
} t_controls;

typedef struct s_data {
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_map *map;
	t_camera *camera;
	t_controls *controls;
} t_data;

/* ************************************************************************** */
/*                          PUBLIC FUNCTION PROTOTYPES                       */
/* ************************************************************************** */

// Core functions
t_map *parse_map(char *filename);
void draw_map(t_data *data);
void free_map(t_map *map);
int handle_close(void *param);

// Event handlers
int handle_keypress(int key, t_data *data);
int handle_keyrelease(int key, t_data *data);
int handle_mouse_press(int button, int x, int y, t_data *data);
int handle_mouse_release(int button, int x, int y, t_data *data);
int handle_mouse_move(int x, int y, t_data *data);

// Rendering functions
t_point project_point(t_point point, t_camera *camera);
int get_color(t_point p1, t_point p2, t_data *data);
t_point apply_shape_transform(t_point point, t_data *data);

#endif
