/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:42:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:50:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

int		mlx_pixel_put(t_xvar *xvar,t_win_list *win,
			      int x,int y,int color)
{
   XGCValues	xgcv;
   
   xgcv.foreground = mlx_int_get_good_color(xvar,color);
   XChangeGC(xvar->display,win->gc,GCForeground,&xgcv);
   XDrawPoint(xvar->display,win->window,win->gc,x,y);
   if (xvar->do_flush)
     XFlush(xvar->display);
}
