/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:54:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 19:27:32 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"
#include <limits.h>

//ft_atoi_base(); -> we will use this function

//this get_file_size is less efficient than lseek system calls
//better than get_next_line idea
static long get_file_size(const char *filename)
{
    long bytes;
    int fd;
    int tot;
    char buffer[1024];

    buffer = NULL;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    bytes = read(fd);
    while (bytes)
    {
        tot += bytes;
        bytes = read(fd,  buffer, sizeof(buffer));
    }
    close(fd);
    return (tot);
}

t_map *parse_map(char *filename)
{
    // get file size for optimal buffer allocation otherwise use realloc
    // read entire file = get_file_size()
    //analyze buffer to get dimensions
    //allocate map structure
    // allocate all points in one contiguous block for better cache performance
    // allocate row pointers
    // set up row pointers to point into contiguous block
    //initialize map
    //parse all lines from buffer
    //
}