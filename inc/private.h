/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:54:45 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 18:54:46 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_H
# define PRIVATE_H

// Private internal functions and definitions
void	*mlx_init(void);
void	*mlx_new_window(void *mlx_ptr, int width, int height, char *title);
int		mlx_key_hook(void *win_ptr, int (*f)(int, void*), void *param);
int		mlx_mouse_hook(void *win_ptr, int (*f)(int, int, int, void*), void *param);
int		mlx_loop_hook(void *mlx_ptr, int (*f)(void*), void *param);
int		mlx_hook(void *win_ptr, int x_event, int x_mask, int (*f)(void*), void *param);
int		mlx_loop(void *mlx_ptr);
int		mlx_destroy_window(void *mlx_ptr, void *win_ptr);
int		mlx_destroy_display(void *mlx_ptr);
int		mlx_do_key_repeatoff(void *win_ptr);

#endif
