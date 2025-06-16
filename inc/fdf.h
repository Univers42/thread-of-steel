/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:27:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 14:36:09 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft/libft.h"

typedef enum e_keycode
{
	KEY_ESC = 65307,
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
	KEY_C = 99,
	KEY_SPACE = 32,
	KEY_R = 114
}			t_keycode;

typedef enum	e_mouse_button
{
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 3,
}				t_mouse_button;


typedef struct	s_data
{
	void	*mlx;
	void	*win;
	int		color;
	int		x;
	int		y;
}				t_data;
void    init_connection();
void    create_window();
void    destroy_window();
void    event_window();
void    close_window();
int handle_keypress(int keycode, void *param);
void draw_simple_object(t_data *data);

#endif
