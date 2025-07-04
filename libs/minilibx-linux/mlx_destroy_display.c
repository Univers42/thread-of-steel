/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:56:35 by mg                #+#    #+#             */
/*   Updated: 2025/07/04 17:54:06 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

/**
 * mlx_destroy_display - Close the connection to the X server.
 * @param xvar Pointer to the X server connection structure.
 * * This function closes the display connection established by mlx_init.
 * * It is typically called when the application is done using the X server
 * * to free resources and clean up.
 */
int	mlx_destroy_display(t_xvar *xvar)
{
	XCloseDisplay(xvar->display);
}
