/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:28:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/05 19:01:16 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>

typedef int		t_coord;
typedef ssize_t	t_dim;
typedef int		t_file_info;
typedef int		t_radix;
typedef char*	t_string;
typedef void*	t_addr;


# define	BUFFER_PARSER	1024
# define	NEWLINE			'\n'
# define	DEFAULT_WHITE	0xFFFFFF
# define	DECIMAL			10
# ifndef RADIX_DEBUG
#  define RADIX_DEBUG		1
# endif

// FSM -like to create the mini super trim
// due to need to skip different string pattern
typedef enum s_state
{
	RADIX = 1 << 0,
	SPACES = 1 << 1,
	NUMS = 1 << 2,
}			t_state;

/**
data structure that handle  the colors with 
 */
typedef struct s_rendu
{
	t_string	color;
	t_radix     hex;		//mayybe int or char*,, I  don¡'t know yet
}				t_rendu;

// we need the points for the color I guess into the map
// it can also be great for extracting different value and avoiding that they overflow if they are huger
// as we express teh point as pixels
typedef struct s_point
{
	t_coord	x;
	t_coord	y;
	t_coord	z;
	int	color;
}			t_point;

/**
	the 
 */
typedef struct s_map
{
	char		**points;		// potentially wrong because don't knoow yet if it will be stack or heap allocated
	t_string	buffer;			//The buffer to parse
	t_dim		height;			// The total of lines
	t_dim		width;			//The total of bytes we encounter in a line
	t_dim		bytes;		// The total bytes of the whole file
	t_dim		min_z;			// Don't kno yet
	t_dim		max_z;			// Don't know yet
}				t_map;

int	should_skip(char c, t_state flags);
ft_trim(t_addr *ptr, t_state flags);
bool	is_negative(t_addr *ptr);
int		ft_isspace(char c);
int		ft_isdigit(char c);
int		ft_isdigit(char c);
int		ft_atoi_base(t_addr str, int radix);
void	get_dimensions(t_string line, t_map *map, int y);
int		parse_line(t_string line, t_map *map, int y);
void	parse_buffer(t_map *map);
t_map	*parse_map(char *filename);


#endif