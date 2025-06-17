/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:37:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 10:26:20 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H
typedef struct  s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct s_map
{
	t_point	**points;
	int		width;
	int		height;
	int		max_z;
	int		min_z;
}				t_map;

// Map scaling functions
typedef struct s_map_bounds {
    int min_value;
    int max_value;
    int range;
} t_map_bounds;

t_map_bounds get_map_bounds(int **map, int width, int height);
void scale_map_values(int **map, int width, int height, int target_range);
void normalize_map(int **map, int width, int height);

#endif