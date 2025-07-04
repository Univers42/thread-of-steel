/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:54:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/05 00:48:51 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"
#include <limits.h>

#include <unistd.h>
#include <fcntl.h>

# define BUFFER_PARSER
# define NEWLINE '\n'

typedef int		t_coord;
typedef ssize_t	t_dim;
typedef char*	t_string;
typedef int		t_file_info;
typedef int		t_signature ;
typedef struct s_rendu
{
	t_string	color;
	t_signature	hex;		//mayybe int or char*,, I  don¡'t know yet
}t_rendu;
typedef struct s_map
{
	char		**points;		// potentially wrong because don't knoow yet if it will be stack or heap allocated
	t_string	buffer;
	t_string	line;
	t_dim		n_raw;
	t_dim		width
	t_dim		bytes;
	t_dim		min_z;
	t_dim		max_z;
	
}				t_map;

typedef struct s_point
{
	t_coord	x;
	t_coord	y;
	
}				t_point;


void	get_dimensions(t_map *map, char *filename)
{
	t_file_info		fd;
	char			buf[1024];
	int				w;
	int				i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	map->row = 0;
	map->width = 0;
	map->bytes = read(fd, buf, 1024); 
	w = 0;
	while (map->bytes)
	{
		i =-1;
		while (++i < map->bytes)
		{
			if (buf[i] == '\n')
			{
				if (w > map->width)
					map->width = w;
				map->row++;
				w = 0;
			}
			else
				w++;
		}
	}
	if (w > 0)
	{
		if (w > map->width)
			map->width = w;
		map->row++;
	}
	close(fd);
}
void	parse_line(t_map *map)
{
	int	x;
	
}

void	parse_buffer(t_map *map)
{
	t_string	line_start;
	t_string	ptr;
	int			curr_line;
	t_dim		parse_width;
	t_coord		x;

	line_start = map->buffer;
	ptr = map->buffer;
	curr_line = 0;
	while (curr_line < height &&  ptr <= (char *)map->buffer + (t_dim)map->bytes)
	{
		if (*ptr == '\n' || ptr == map->buffer + map->bytes)
		{
			*ptr = '\0';
			parsed_width = parse_line(line_start, &map, current_line);
			x = -1;
			while (++x < parsed_width)
			{
				map->points[curr_line][x].x = x - width / 2;
				map->points[curr_line][x].y = curr_line - height / 2;
			}
			curr_line++;
			line_start = ptr + 1;
		}
		ptr++;
	}
}
t_map	*parse_map(char *filename)
{
	t_file_info	fd;
	t_dim		bytes_read;
	t_map		map;
	t_point		*all_points;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map *));
	if (!map)
		return (NULL);
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	if (!get_dimensions(&map, filename))
		return ("Error while getting dimensions", NULL);
	ft_printf("new datas to verify the accuracy:\n"
		"bytes: %d \n width: %d \n line_count : %d \n");
	map->buffer = malloc(map->bytes + 1);
	if (!map->buffer)
		return (close(fd), NULL);
	bytes_read = read(fd, map->buffer, map->bytes);
	close(fd);
	if (bytes_read != file_size)
		return (free(map->buffer), NULL);
	map->buffer[map->bytes] = NEWLINE;
	if (!map->width || !map->n_raw)
		return (free(buffer), NULL);
	all_points = malloc(sizeof(t_point *) * map->n_raw  * map->width);
	if (!all_points)
		return  (free(buffer), free(map), NULL);
	map->points = malloc(sizeof(t_point *) * map->n_raw);
	if (map->points)
		return (free(buffer), free(map), free(all_points), NULL);
	i = 0;
	while (++i < height)
		map->points[i] = all_points + (i * width);
	parse_buffer(&map);
	free(map->buffer);
	map->buffer = NULL;
	return (map);
}