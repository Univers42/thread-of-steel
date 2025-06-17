/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 11:01:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
typedef struct s_map_point
{
    int z;
    int color;
    int visited;
} t_map_point;

typedef struct s_map
{
    t_map_point **points;
    int width;
    int height;
} t_map;

// Parse a simple map (Z values only for editing)
t_map *parse_simple_map(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    
    // Count lines and width
    char line[1024];
    int height = 0, width = 0;
    
    while (fgets(line, sizeof(line), file))
    {
        if (height == 0)
        {
            // Count elements in first line
            char *token = strtok(line, " \t\n");
            while (token)
            {
                width++;
                token = strtok(NULL, " \t\n");
            }
        }
        height++;
    }
    
    rewind(file);
    
    // Allocate map
    t_map *map = malloc(sizeof(t_map));
    map->width = width;
    map->height = height;
    map->points = malloc(sizeof(t_map_point*) * height);
    
    for (int i = 0; i < height; i++)
        map->points[i] = malloc(sizeof(t_map_point) * width);
    
    // Parse values
    int y = 0;
    while (fgets(line, sizeof(line), file) && y < height)
    {
        char *token = strtok(line, " \t\n");
        int x = 0;
        
        while (token && x < width)
        {
            // Parse z value (ignore color for simplicity)
            map->points[y][x].z = atoi(token);
            map->points[y][x].color = 0xFFFFFF;
            map->points[y][x].visited = 0;
            
            token = strtok(NULL, " \t\n");
            x++;
        }
        y++;
    }
    
    fclose(file);
    return map;
}

// Save map back to file
void save_map(t_map *map, char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file) return;
    
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            fprintf(file, "%d", map->points[y][x].z);
            if (x < map->width - 1)
                fprintf(file, " ");
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
}

// Reset visited flags
void reset_visited(t_map *map)
{
    for (int y = 0; y < map->height; y++)
        for (int x = 0; x < map->width; x++)
            map->points[y][x].visited = 0;
}

// Flood fill algorithm
void flood_fill(t_map *map, int x, int y, int old_value, int new_value)
{
    // Bounds check
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return;
    
    // Already visited or wrong value
    if (map->points[y][x].visited || map->points[y][x].z != old_value)
        return;
    
    // Mark as visited and change value
    map->points[y][x].visited = 1;
    map->points[y][x].z = new_value;
    
    // Recursively fill adjacent cells (4-connected)
    flood_fill(map, x + 1, y, old_value, new_value);
    flood_fill(map, x - 1, y, old_value, new_value);
    flood_fill(map, x, y + 1, old_value, new_value);
    flood_fill(map, x, y - 1, old_value, new_value);
}

// Replace all occurrences of a value
void replace_all(t_map *map, int old_value, int new_value)
{
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if (map->points[y][x].z == old_value)
                map->points[y][x].z = new_value;
        }
    }
}

// Add noise to map
void add_noise(t_map *map, int intensity)
{
    srand(42); // Fixed seed for reproducible results
    
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            int noise = (rand() % (intensity * 2 + 1)) - intensity;
            map->points[y][x].z += noise;
        }
    }
}

// Smooth map using average filter
void smooth_map(t_map *map, int iterations)
{
    for (int iter = 0; iter < iterations; iter++)
    {
        t_map_point **new_points = malloc(sizeof(t_map_point*) * map->height);
        for (int i = 0; i < map->height; i++)
            new_points[i] = malloc(sizeof(t_map_point) * map->width);
        
        for (int y = 0; y < map->height; y++)
        {
            for (int x = 0; x < map->width; x++)
            {
                int sum = 0, count = 0;
                
                // Average with neighbors
                for (int dy = -1; dy <= 1; dy++)
                {
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        int nx = x + dx, ny = y + dy;
                        if (nx >= 0 && nx < map->width && ny >= 0 && ny < map->height)
                        {
                            sum += map->points[ny][nx].z;
                            count++;
                        }
                    }
                }
                
                new_points[y][x].z = sum / count;
                new_points[y][x].color = map->points[y][x].color;
                new_points[y][x].visited = 0;
            }
        }
        
        // Replace old points
        for (int i = 0; i < map->height; i++)
            free(map->points[i]);
        free(map->points);
        map->points = new_points;
    }
}

// Create a gradient pattern
void create_gradient(t_map *map, int min_val, int max_val, int direction)
{
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            float ratio = 0.0;
            
            switch (direction)
            {
                case 0: // Horizontal
                    ratio = (float)x / (map->width - 1);
                    break;
                case 1: // Vertical
                    ratio = (float)y / (map->height - 1);
                    break;
                case 2: // Diagonal
                    ratio = (float)(x + y) / (map->width + map->height - 2);
                    break;
                case 3: // Radial
                    {
                        float cx = map->width / 2.0;
                        float cy = map->height / 2.0;
                        float max_dist = sqrt(cx*cx + cy*cy);
                        float dist = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));
                        ratio = dist / max_dist;
                    }
                    break;
            }
            
            if (ratio > 1.0) ratio = 1.0;
            map->points[y][x].z = min_val + (int)(ratio * (max_val - min_val));
        }
    }
}

// Print map statistics
void print_stats(t_map *map)
{
    int min_z = map->points[0][0].z;
    int max_z = map->points[0][0].z;
    long sum = 0;
    
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            int z = map->points[y][x].z;
            if (z < min_z) min_z = z;
            if (z > max_z) max_z = z;
            sum += z;
        }
    }
    
    printf("Map Statistics:\n");
    printf("  Size: %dx%d (%d points)\n", map->width, map->height, map->width * map->height);
    printf("  Z Range: %d to %d (range: %d)\n", min_z, max_z, max_z - min_z);
    printf("  Average Z: %.2f\n", (float)sum / (map->width * map->height));
}

// Print usage
void print_usage(char *program)
{
    printf("FDF Map Editor - Utility for editing heightmap files\n\n");
    printf("Usage: %s <command> <input_file> [output_file] [params...]\n\n", program);
    printf("Commands:\n");
    printf("  flood <x> <y> <new_value>     - Flood fill from point (x,y)\n");
    printf("  replace <old> <new>           - Replace all old values with new\n");
    printf("  noise <intensity>             - Add random noise (±intensity)\n");
    printf("  smooth <iterations>           - Smooth map using average filter\n");
    printf("  gradient <min> <max> <dir>    - Create gradient (dir: 0=horiz, 1=vert, 2=diag, 3=radial)\n");
    printf("  stats                         - Show map statistics only\n");
    printf("  info                          - Show detailed map information\n");
    printf("\nExamples:\n");
    printf("  %s flood elem-col.fdf output.fdf 2 3 15\n", program);
    printf("  %s replace map.fdf new.fdf 0 5\n", program);
    printf("  %s noise map.fdf noisy.fdf 3\n", program);
    printf("  %s gradient empty.fdf mountain.fdf 0 20 1\n", program);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        print_usage(argv[0]);
        return 1;
    }
    
    char *command = argv[1];
    char *input_file = argv[2];
    char *output_file = argc > 3 ? argv[3] : "output.fdf";
    
    t_map *map = parse_simple_map(input_file);
    if (!map)
    {
        printf("Error: Could not parse map file '%s'\n", input_file);
        return 1;
    }
    
    printf("Loaded map: %dx%d\n", map->width, map->height);
    
    if (strcmp(command, "flood") == 0)
    {
        if (argc < 7)
        {
            printf("Usage: flood <x> <y> <new_value>\n");
            return 1;
        }
        
        int x = atoi(argv[4]);
        int y = atoi(argv[5]);
        int new_value = atoi(argv[6]);
        
        if (x >= 0 && x < map->width && y >= 0 && y < map->height)
        {
            int old_value = map->points[y][x].z;
            printf("Flood filling from (%d,%d): %d -> %d\n", x, y, old_value, new_value);
            
            reset_visited(map);
            flood_fill(map, x, y, old_value, new_value);
            save_map(map, output_file);
            printf("Saved to '%s'\n", output_file);
        }
        else
        {
            printf("Error: Point (%d,%d) is out of bounds\n", x, y);
        }
    }
    else if (strcmp(command, "replace") == 0)
    {
        if (argc < 6)
        {
            printf("Usage: replace <old_value> <new_value>\n");
            return 1;
        }
        
        int old_val = atoi(argv[4]);
        int new_val = atoi(argv[5]);
        
        printf("Replacing all %d with %d\n", old_val, new_val);
        replace_all(map, old_val, new_val);
        save_map(map, output_file);
        printf("Saved to '%s'\n", output_file);
    }
    else if (strcmp(command, "noise") == 0)
    {
        if (argc < 5)
        {
            printf("Usage: noise <intensity>\n");
            return 1;
        }
        
        int intensity = atoi(argv[4]);
        printf("Adding noise with intensity ±%d\n", intensity);
        add_noise(map, intensity);
        save_map(map, output_file);
        printf("Saved to '%s'\n", output_file);
    }
    else if (strcmp(command, "smooth") == 0)
    {
        if (argc < 5)
        {
            printf("Usage: smooth <iterations>\n");
            return 1;
        }
        
        int iterations = atoi(argv[4]);
        printf("Smoothing map (%d iterations)\n", iterations);
        smooth_map(map, iterations);
        save_map(map, output_file);
        printf("Saved to '%s'\n", output_file);
    }
    else if (strcmp(command, "gradient") == 0)
    {
        if (argc < 7)
        {
            printf("Usage: gradient <min> <max> <direction>\n");
            return 1;
        }
        
        int min_val = atoi(argv[4]);
        int max_val = atoi(argv[5]);
        int direction = atoi(argv[6]);
        
        char *dir_names[] = {"horizontal", "vertical", "diagonal", "radial"};
        printf("Creating %s gradient: %d to %d\n", 
               dir_names[direction % 4], min_val, max_val);
        
        create_gradient(map, min_val, max_val, direction);
        save_map(map, output_file);
        printf("Saved to '%s'\n", output_file);
    }
    else if (strcmp(command, "stats") == 0)
    {
        print_stats(map);
    }
    else if (strcmp(command, "info") == 0)
    {
        print_stats(map);
        printf("\nFirst few values:\n");
        for (int y = 0; y < (map->height < 5 ? map->height : 5); y++)
        {
            printf("Row %d: ", y);
            for (int x = 0; x < (map->width < 10 ? map->width : 10); x++)
            {
                printf("%3d ", map->points[y][x].z);
            }
            if (map->width > 10) printf("...");
            printf("\n");
        }
        if (map->height > 5) printf("...\n");
    }
    else
    {
        printf("Unknown command: %s\n", command);
        print_usage(argv[0]);
        return 1;
    }
    
    return 0;
}
