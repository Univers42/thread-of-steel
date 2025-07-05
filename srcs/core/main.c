/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:40:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/05 22:04:02 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"


/**
 * if we open the file just once,  we keep the var in a local scope
 * otherwise in a datastructuer
 */
void create_map(t_map *map, s_file file)
{
	map->map = (t_map *)malloc(sizeof(t_map *));
	if (!map->map)
	{
		ft_putstr_fd("Error allocating memory for map.\n", 2);
		return (NULL);
	}
	map->line = get_next_line(file.fd) > 0;
	while (map->line)
	{
		map->line = get_next_line(file.fd);
		if (!map->line)
		{
			ft_putstr_fd("Error reading line.\n", 2);
			free(map->map);
			close(file.fd);
			return ;
		}
		*map->map++ = map->line;
		free(map->line);
	}
	if (ret < 0)
		ft_putstr_fd("Error reading file.\n", 2);
	close(file.fd);	
}

static inline bool valid_input()
{
	if (!map | !file | file->fd < 0)
	{
		ft_putstr_fd("Invalid input parameters.\n", 2);
		return (false);
	}

}

static int initialization(argc, argv)
{
	int	fd;

	if (argc != 3)
		return (ft_putstr_fd("Usage: ./fdf <map_file> <window_size>\n", 2, 1));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error opening file.\n", 2);
		return (1);
	}
	parse_map(argv1, fd);
}

static int shutdown()
{
	close(fd);
	// free allocated memory
	ft_putstr_fd("FDF closed successfully.\n", 1);
	mlx_destroy_display(xvar);
	
	return (1);
}

static int start_sim()
{
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.map = parse_map(argv[1]);
	if (!data.map)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return(1);
	}
}

void	print_controls(void)
{
	const char *messages[8]=
	{
		{"=== FDF CONTROLS ==="},
		{"WASD/Arrow keys: Move"},
		{"Mouse drag: Rotate"},
		{"Q/E: Rotate Z-axis"},
		{"+/-: Zoom"},
		{"Mouse wheel"},
		{"0: Show embedded colors (default white)"},
		{"1-9: color themes"},
		{"Alt+1-9: shape transforms"},
		{"Tab: Cycle themes"},
		{"Alt + tab: Cycle shapes"},
		{"Space: Change colors"},
		{"ESC: Exit"}
	}
	while (*messages)
		ft_putendl(messages++, STDOUT_FILENO);
}

int main(int argc, char **arv)
{
	t_string str;
	int		ret;
	t_data data;
	t_camera *camera;
	t_controls	*controls;
	
	if (!valid_input(argc, argv))
		return (ft_putstr_fd("Invalid input parameters.\n", 2, 1));
	if (preload(argc, argv))
		return (ft_putstr_fd("Initialization failed.\n", 2, 1));
	if (!sim())
		return (ft_putrstr("Initialization failed.\n", 2, 1));
	mlx_do_key_repeatoff(data.mlx);
	print_controls();
	mlx_loop(data.mlx);
	return (0);
}