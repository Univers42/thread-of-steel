/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_clear_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:37:27 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:37:27 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
 * mlx_clear_window - Clear the specified window.
 * it just clear\wipe the window content
 * @param xvar Point to the X server connection strcture
 * @param win Pointer to the window list structure
 * @return 0 on success, or -1 on failure.
 * @note this function XClearWindow on the specified window,
 * effectively clearing its contents. 
 * it is tipically used to refresh the window before drawing new content
 * 
 */
int		mlx_clear_window(t_xvar *xvar,t_win_list *win)
{
  XClearWindow(xvar->display,win->window);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
