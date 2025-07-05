/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:27:52 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/05 21:42:59 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void parse_z(t_map *map, t_addr ptr, t_addr coords)
{
	int *x = (int *)coords;
	int *y = (int *)((char *)coords + sizeof(int));
	int z_val;
	int color;
	
	*x = 0;
	while (*(char *)ptr && *(char *)ptr != '\n' && *(char *)ptr != '\0')
	{
		ft_trim(&ptr, TRIM_SPACES);
		if (!*(char *)ptr || *(char *)ptr == '\n')
			break;
		
		// Extract z value directly into memory
		cumul_value(&ptr, &z_val);
		color = DEFAULT_WHITE;
		
		// Check for color
		if (*(char *)ptr == ',')
		{
			ptr = (char *)ptr + 1;
			ft_trim(&ptr, TRIM_SPACES);
			extract_hex(&ptr, &color);
		}
		
		// Store directly in map structure
		map->points[*y][*x].x = *x;
		map->points[*y][*x].y = *y;
		map->points[*y][*x].z = z_val;
		map->points[*y][*x].color = color;
		
		// Update min/max dynamically
		if (z_val < map->min_z)
			map->min_z = z_val;
		if (z_val > map->max_z)
			map->max_z = z_val;
		
		if (RADIX_DEBUG && color != DEFAULT_WHITE)
			printf("Parsed color: 0x%06X at (%d, %d)\n", color, *x, *y);
	
		(*x)++;
		ft_trim(&ptr, TRIM_SPACES);
	}
}


void get_dimensions(t_map *map, char *filename)
{
	t_file_info fd;
	char buf[BUFFER_PARSER];
	t_addr buf_ptr;
	int bytes_read;
	int current_width = 0;
	int in_number = 0;  // Flag to track if we're inside a number/data point
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return;
	
	// Initialize map dimensions using direct memory access
	*(t_dim *)&map->height = 0;
	*(t_dim *)&map->width = 0;
	*(t_dim *)&map->bytes = 0;
	
	while ((bytes_read = read(fd, buf, BUFFER_PARSER)) > 0)
	{
		map->bytes += bytes_read;
		buf_ptr = buf;
		
		while (buf_ptr < (t_addr)(buf + bytes_read))
		{
			char current_char = *(char *)buf_ptr;
			
			if (current_char == '\n')
			{
				if (current_width > map->width)
					map->width = current_width;
				map->height++;
				current_width = 0;
				in_number = 0;
			}
			else if (current_char == ' ' || current_char == '\t')
			{
				in_number = 0;  // We're no longer in a number
			}
			else if (!in_number)
			{
				// We're starting a new data point
				current_width++;
				in_number = 1;
			}
			// If in_number is 1 and we're not at whitespace or newline,
			// we're still in the same data point, so don't increment
			
			buf_ptr = (char *)buf_ptr + 1;
		}
	}
	
	// Handle case where file doesn't end with newline
	if (current_width > 0)
	{
		if (current_width > map->width)
			map->width = current_width;
		map->height++;
	}
	
	close(fd);
}


void parse_buffer(t_map *map)
{
	t_addr line_start;
	t_addr ptr;
	int coords[2]; // x, y coordinates for dynamic passing
	
	line_start = map->buffer;
	ptr = map->buffer;
	coords[1] = 0; // y coordinate
	
	while (coords[1] < map->height && ptr <= (t_addr)((char *)map->buffer + map->bytes))
	{
		if (*(char *)ptr == '\n' || ptr == (t_addr)((char *)map->buffer + map->bytes))
		{
			*(char *)ptr = '\0';
			coords[0] = 0; // Reset x coordinate
			parse_z(map, line_start, coords);
			coords[1]++;
			line_start = (char *)ptr + 1;
		}
		ptr = (char *)ptr + 1;
	}
}

t_map *parse_map(char *filename)
{
	t_file_info fd;
	t_addr map_ptr;
	t_addr all_points;
	t_dim bytes_read;
	int i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	
	// Allocate map using generic pointer
	map_ptr = malloc(sizeof(t_map));
	if (!map_ptr)
		return (NULL);
	
	t_map *map = (t_map *)map_ptr;
	
	// Initialize with extreme values for dynamic min/max tracking
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	
	// Get dimensions dynamically
	get_dimensions(map, filename);
	
	if (RADIX_DEBUG)
		printf("Dimensions: width=%ld, height=%ld, bytes=%ld\n", 
			map->width, map->height, map->bytes);
	
	// Dynamic buffer allocation
	map->buffer = malloc(map->bytes + 1);
	if (!map->buffer)
	{
		free(map_ptr);
		return (NULL);
	}
	
	// Read entire file into buffer
	bytes_read = read(fd, map->buffer, map->bytes);
	close(fd);
	
	if (bytes_read != map->bytes)
	{
		free(map->buffer);
		free(map_ptr);
		return (NULL);
	}
	
	*(char *)(map->buffer + map->bytes) = '\0';
	
	// Dynamic point allocation - single block for efficiency
	all_points = malloc(sizeof(t_point) * map->height * map->width);
	if (!all_points)
	{
		free(map->buffer);
		free(map_ptr);
		return (NULL);
	}
	
	// Dynamic pointer array allocation
	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
	{
		free(all_points);
		free(map->buffer);
		free(map_ptr);
		return (NULL);
	}
	
	// Set up 2D array pointers dynamically
	i = 0;
	while (i < map->height)
	{
		map->points[i] = (t_point *)((char *)all_points + (i * map->width * sizeof(t_point)));
		i++;
	}
	
	// Parse buffer using dynamic approach
	parse_buffer(map);
	
	// Free buffer - no longer needed after parsing
	free(map->buffer);
	map->buffer = NULL;
	
	return (map);
}