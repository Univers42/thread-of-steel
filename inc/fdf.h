/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:40:39 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:15:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"

typedef enum s_theme
{
	DEFAULT,
	DARK,
	PUNK,
	RETRO,
	EARTH,
	SPACE
}			t_theme;

/**
 * 
 */
typedef enum s_key
{
	key_up = 126
}			t_key;
typedef struct s_map
{
	char	**map;
	char	*line;
	int 	rows;
	int 	cols;
	int 	capacity;
}t_map;

typedef struct s_file
{
	int		fd;
	char 	*filename;	
}				t_file;

typedef struct s_anim
{
	
}

typedef struct win
{
	int     width;
	int     height;
	char    *title;
}   t_win;

// PARSER

// MOTION

// UTILS

//OPTIMIZATION

#endif