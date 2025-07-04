/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:27:42 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 18:40:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# define INIT_CAPACITY 10

void	map_struct_init(t_map *map)
{
	t_map *map;

	map = (t_map *)malloc(t_map *);
	if (!map)
	{
		ft_putstr_fd("Error allocating memory for map.\n", 2);
		rerturn (1);
	}
	ft_memset(map, 0, sizeof(t_map));
	*map->capacity = INIT_CAPACITY;
}

void gen_map(t_map *map)
{
	if (!map || map->capacity <= )
	{
		ft_putstr_fd("Invalid initialization of map_struct.\n", 2);
		return ;
	}
	map->map = (char **)malloc(sizeof(char *) * map->capacity);
	if (!map->map)
	{
		ft_putstr_fd("Error allocating memory for map..\n", 2);
		return ;
	}
	// if the capacity is less than the count of rows, we need to reallocate
	
	if (map->rows > map->capacity)
	{
		new_map = (char **)ft_realloc(map->map, sizeof(char *) * map->capacity, sizeof(char *) * map->rows);
		map->map = new_map;
	}
	
	return (init);
}