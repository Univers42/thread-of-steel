#ifndef FDF_PRIVATE_H
# define FDF_PRIVATE_H

# include "fdf_public.h"
# include "motion.h"
# include "optimization.h"
# include "parsing.h"
# include "utils.h"

/* ************************************************************************** */
/*                          PRIVATE IMPLEMENTATION DETAILS                   */
/* ************************************************************************** */

// Internal rendering functions
void draw_line(t_data *data, t_point *p1, t_point *p2);
void draw_line_fast(t_data *data, t_point *p1, t_point *p2);
void draw_map_optimized(t_data *data);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);

// Performance optimization functions
int is_line_visible(t_point p1, t_point p2, int width, int height);
int calculate_view_hash(t_data *data);
int clip_line(t_point *p1, t_point *p2, int width, int height);

// Color and theme functions
int get_themed_color(int z_value, int min_z, int max_z, int theme);
const char* get_theme_name(int theme);
int handle_theme_switch(int key, t_data *data);
void cycle_color_theme(t_data *data);

// Camera and projection functions
void init_rotation_matrix(t_camera *camera);

// Parser internal functions
t_point *parse_line(char *line, int y, int width);

float vlength(const float *v);
void vcross(const float *v1, const float *v2, float *cross);
void vcopy(const float *v1, float *v2);
void vset(float *v, float x, float y, float z);
void vzero(float *v);
void apply_trackball_rotation(t_camera *camera, float dx, float dy);
// Parser internal functions
t_point *parse_line(char *line, int y, int width);

#endif
