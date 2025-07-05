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

#include "fdf.h"
#include <string.h>

//forward prototypes
void			event_hooks(t_addr mlx_ptr, t_addr win_ptr);
static int		start_sim(void);
void			print_controls(void);

// Global variables for MLX
static t_addr g_mlx_ptr = NULL;
static t_addr g_win_ptr = NULL;

int main(int argc, char **argv)
{
	if (!valid_input(argc, argv))
	{
		ft_putstr_fd("Invalid input parameters.\n", 2);
		return (1);
	}
	if (preload(argc, argv))
	{
		ft_putstr_fd("Initialization failed.\n", 2);
		return (1);
	}
	if (!start_sim())
	{
		ft_putstr_fd("Simulation failed.\n", 2);
		return (1);
	}
	return (0);
}

int valid_input(int argc, char **argv)
{
	return (argc == 2 && argv[1] != NULL);
}

int preload(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (0);
}

int key_event_handler(int keycode, t_addr param)
{
	(void)param;
	if (keycode == KEY_ESC || keycode == KEY_Q)
		return (shutdown(NULL));
	return (0);
}

int shutdown(t_addr param)
{
	(void)param;
	if (g_win_ptr && g_mlx_ptr)
		mlx_destroy_window(g_mlx_ptr, g_win_ptr);
	if (g_mlx_ptr)
		mlx_destroy_display(g_mlx_ptr);
	exit(0);
	return (0);
}

static int start_sim(void)
{
	g_mlx_ptr = mlx_init();
	if (!g_mlx_ptr)
		return (0);
	g_win_ptr = mlx_new_window(g_mlx_ptr, WIDTH_WIN, HEIGHT_WIN, "FDF");
	if (!g_win_ptr)
	{
		ft_putstr_fd("Error creating window.\n", 2);
		mlx_destroy_display(g_mlx_ptr);
		return (0);
	}
	event_hooks(g_mlx_ptr, g_win_ptr);
	mlx_do_key_autorepeatoff(g_mlx_ptr);
	print_controls();
	mlx_loop(g_mlx_ptr);
	return (1);
}


/**
@note as I use directly an array in the stack this is not a lvalue
 * so I can use it as a pointer to the first element of the array
 * and then iterate through the array using pointer arithmetic.
 * This is a safe way to print the controls without using dynamic memory allocation.
 * @note this function is used to print the controls of the FDF program.
 * It is called at the start of the program to inform the user about the controls.
 maybe to maximize the modularity I could create a wrapper function
 * that takes a pointer to the first element of the array and prints it.
*/
void	print_controls(void)
{
	t_addr	ptr;
	const char *messages[]=
	{
		"=== FDF CONTROLS ===",
		"WASD/Arrow keys: Move",
		"Mouse drag: Rotate",
		"Q/E: Rotate Z-axis",
		"+/-: Zoom",
		"Mouse wheel",
		"0: Show embedded colors (default white)",
		"1-9: color themes",
		"Alt+1-9: shape transforms",
		"Tab: Cycle themes",
		"Alt + tab: Cycle shapes",
		"Space: Change colors",
		"ESC: Exit",
		NULL
	};
	ptr = (t_addr)messages;
	while (*(const char **)ptr)
	{
		puts(*(const char **)(ptr));
		ptr = (t_addr)((const char **)ptr + 1);
	}
}

void event_hooks(t_addr mlx_ptr, t_addr win_ptr)
{
	(void)mlx_ptr;
	(void)win_ptr;
	// TODO: Add your event hook registrations here
}
