/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:40:39 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/05 21:44:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "achi.h"
# include "fsm.h"
# include "geometry.h"
# include "internal.h"
# include "config.h"

# define	BUFFER_PARSER	1024
# define	NEWLINE			'\n'
# define	DEFAULT_WHITE	0xFFFFFF
# define	DECIMAL			10
# define	WIDTH_WIN		1200
# define	HEIGHT_WIN		800
# define	DestroyNotify	17
# ifndef RADIX_DEBUG
#  define RADIX_DEBUG		1
# endif

// we need the points for the color I guess into the map
// it can also be great for extracting different value and
// avoiding that they overflow if they are huger
// as we express teh point as pixels
typedef struct s_point
{
	t_coord	x;
	t_coord	y;
	t_coord	z;
	int	color;
}			t_point;

/**
this is a parser structure that is just to be used for extracting 
correctly and cleanly all the value we need to build our project
 */
typedef struct s_map
{
	t_point		**points;		// Fix: should be t_point** not char**
	t_string	buffer;			//The buffer to parse
	t_dim		height;			// The total of lines
	t_dim		width;			//The total of bytes we encounter in a line
	t_dim		bytes;			// The total bytes of the whole file
	t_dim		min_z;			// Don't kno yet
	t_dim		max_z;			// Don't know yet
}				t_map;

/**
	When we will open our windows, this structure will be the core data
	of window's  configuration. for instance the dimensions are needed
	to be change we cannchange them.
 */
typedef struct win
{
	t_dim		width;		// dimensions horizontal byte/byte
	t_dim		height;		// dimensions vertcial byte/byte
	t_string	title;		// title of the structure
}				t_win;



/**
data structure that handle  the colors with 
 */
typedef struct s_rendu
{
	t_string	color;
	t_radix     hex;		//mayybe int or char*,, I  don¡'t know yet
}				t_rendu;


int		should_skip(char c, t_state flags);
void	ft_trim(t_addr *ptr, t_state flags);
int		extract_sign(t_addr *ptr);
int		cumul_value(t_addr *ptr, t_addr target);
int		extract_hex(t_addr *ptr, t_addr result);
void	advance_ptr(t_addr *ptr, char delimiter);
void	parse_z(t_map *map, t_addr ptr, t_addr coords);
bool	is_negative(t_addr *ptr);
void	get_dimensions(t_map *map, char *filename);
int		parse_line(t_string line, t_map *map, int y);
void	parse_buffer(t_map *map);
t_map	*parse_map(char *filename);

// Missing type definitions
typedef struct s_data
{
	t_addr	mlx_ptr;
	t_addr	win_ptr;
	t_addr	img_ptr;
	t_string	addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_map	*map;
}			t_data;

typedef struct s_camera
{
	double	zoom;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	int		offset_x;
	int		offset_y;
	int		projection;
}			t_camera;

typedef struct s_controls
{
	int		theme;
	int		shape;
	int		colors_enabled;
}			t_controls;

// Function prototypes
int		valid_input(int argc, char **argv);
int		preload(int argc, char **argv);
int		sim(void);
int		key_event_handler(int keycode, t_addr param);
int		mouse_event_handler(int button, int x, int y, t_addr param);
int		loop_event_handler(t_addr param);
int		shutdown(t_addr param);
int		close_handler(void);

#endif