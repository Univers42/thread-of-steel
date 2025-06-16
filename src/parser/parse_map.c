/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:52:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/16 21:02:19 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <limits.h>

// Fast hex to int conversion without string operations
static int fast_hex_to_int(const char *hex_str)
{
    int result = 0;
    int i = 0;
    
    // Skip "0x" prefix
    if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
        i = 2;
    
    while (hex_str[i])
    {
        result <<= 4;
        if (hex_str[i] >= '0' && hex_str[i] <= '9')
            result += hex_str[i] - '0';
        else if (hex_str[i] >= 'a' && hex_str[i] <= 'f')
            result += hex_str[i] - 'a' + 10;
        else if (hex_str[i] >= 'A' && hex_str[i] <= 'F')
            result += hex_str[i] - 'A' + 10;
        i++;
    }
    return result;
}

// Optimized line parsing without multiple allocations
static int parse_line_optimized(char *line, t_point *points, int y, int width, int *min_z, int *max_z)
{
    int x = 0;
    char *ptr = line;
    int z_val;
    int color;
    
    // Skip leading whitespace
    while (*ptr == ' ' || *ptr == '\t')
        ptr++;
    
    while (*ptr && x < width)
    {
        // Parse Z value
        z_val = 0;
        int negative = 0;
        if (*ptr == '-')
        {
            negative = 1;
            ptr++;
        }
        
        while (*ptr >= '0' && *ptr <= '9')
        {
            z_val = z_val * 10 + (*ptr - '0');
            ptr++;
        }
        
        if (negative)
            z_val = -z_val;
        
        // Check for color
        color = 0xFFFFFF; // default white
        if (*ptr == ',')
        {
            ptr++; // skip comma
            if (*ptr == '0' && (*(ptr+1) == 'x' || *(ptr+1) == 'X'))
            {
                color = fast_hex_to_int(ptr);
                // Skip to end of hex value
                ptr += 2;
                while ((*ptr >= '0' && *ptr <= '9') || 
                       (*ptr >= 'a' && *ptr <= 'f') || 
                       (*ptr >= 'A' && *ptr <= 'F'))
                    ptr++;
            }
        }
        
        // Set point data
        points[x].x = x;
        points[x].y = y;
        points[x].z = z_val;
        points[x].color = color;
        
        // Update min/max Z
        if (z_val < *min_z) *min_z = z_val;
        if (z_val > *max_z) *max_z = z_val;
        
        x++;
        
        // Skip to next number
        while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '\n')
            ptr++;
        while (*ptr == ' ' || *ptr == '\t')
            ptr++;
    }
    
    return x;
}

// Pre-calculate file size for optimal memory allocation
static long get_file_size(int fd)
{
    long size;
    long current_pos = lseek(fd, 0, SEEK_CUR);
    
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, current_pos, SEEK_SET);
    
    return size;
}

// Count lines and get width in a single pass through buffer
static int analyze_buffer(char *buffer, long size, int *width)
{
    int lines = 0;
    int current_width = 0;
    int max_width = 0;
    char *ptr = buffer;
    char *end = buffer + size;
    
    while (ptr < end)
    {
        if (*ptr == '\n' || ptr == end - 1)
        {
            if (current_width > max_width)
                max_width = current_width;
            if (current_width > 0)
                lines++;
            current_width = 0;
        }
        else if (*ptr != ' ' && *ptr != '\t')
        {
            // Skip to end of current number/token
            while (ptr < end && *ptr != ' ' && *ptr != '\t' && *ptr != '\n')
                ptr++;
            current_width++;
            continue;
        }
        ptr++;
    }
    
    *width = max_width;
    return lines;
}

// Ultra-efficient single-pass parser
t_map *parse_map(char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return NULL;
    
    // Get file size for optimal buffer allocation
    long file_size = get_file_size(fd);
    if (file_size <= 0)
    {
        close(fd);
        return NULL;
    }
    
    // Read entire file into buffer at once
    char *buffer = malloc(file_size + 1);
    if (!buffer)
    {
        close(fd);
        return NULL;
    }
    
    long bytes_read = read(fd, buffer, file_size);
    close(fd);
    
    if (bytes_read != file_size)
    {
        free(buffer);
        return NULL;
    }
    buffer[file_size] = '\0';
    
    // Analyze buffer to get dimensions
    int width, height;
    height = analyze_buffer(buffer, file_size, &width);
    
    if (height == 0 || width == 0)
    {
        free(buffer);
        return NULL;
    }
    
    // Allocate map structure
    t_map *map = malloc(sizeof(t_map));
    if (!map)
    {
        free(buffer);
        return NULL;
    }
    
    // Allocate all points in one contiguous block for better cache performance
    t_point *all_points = malloc(sizeof(t_point) * width * height);
    if (!all_points)
    {
        free(buffer);
        free(map);
        return NULL;
    }
    
    // Allocate row pointers
    map->points = malloc(sizeof(t_point*) * height);
    if (!map->points)
    {
        free(buffer);
        free(map);
        free(all_points);
        return NULL;
    }
    
    // Set up row pointers to point into contiguous block
    for (int i = 0; i < height; i++)
        map->points[i] = all_points + (i * width);
    
    // Initialize map
    map->width = width;
    map->height = height;
    map->min_z = INT_MAX;
    map->max_z = INT_MIN;
    
    // Parse all lines from buffer
    char *line_start = buffer;
    char *ptr = buffer;
    int current_line = 0;
    
    while (current_line < height && ptr <= buffer + file_size)
    {
        if (*ptr == '\n' || ptr == buffer + file_size)
        {
            *ptr = '\0'; // temporarily null-terminate
            
            // Parse this line directly into points array
            int parsed_width = parse_line_optimized(line_start, 
                                                   map->points[current_line], 
                                                   current_line, 
                                                   width, 
                                                   &map->min_z, 
                                                   &map->max_z);
            
            // Center coordinates for better display
            for (int x = 0; x < parsed_width; x++)
            {
                map->points[current_line][x].x = x - width / 2;
                map->points[current_line][x].y = current_line - height / 2;
            }
            
            current_line++;
            line_start = ptr + 1;
        }
        ptr++;
    }
    
    free(buffer);
    return map;
}

