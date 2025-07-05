/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 19:15:46 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/05 21:42:47 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int main(int argc, char **argv)
{
	t_map *map;
	
	if (argc != 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return (1);
	}
	
	map = parse_map(argv[1]);
	if (!map)
	{
		printf("Error: Failed to parse map file\n");
		return (1);
	}
	
	printf("Map parsed successfully!\n");
	printf("Dimensions: %ld x %ld\n", map->width, map->height);
	printf("Z range: %ld to %ld\n", map->min_z, map->max_z);
	
	// Clean up
	if (map->points)
		free(map->points[0]); // Free the contiguous block
	free(map->points);
	free(map);
	
	return (0);
}
