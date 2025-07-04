/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:51:13 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:59:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

/**
  @note
  @param xvar the pointer to the server
  @param win pointer to window datas
  @param x abscices on the orthodox plan
  @param y ordonate on the orthodox plan
  @param color the key code's color
  @param string pointer to the first character
  @return 1 || 0 dependiing 
 */
int		mlx_string_put(t_xvar *xvar,t_win_list *win,
			       int x,int y,int color,char *string)
{
   XGCValues	xgcv;
   
   xgcv.foreground = mlx_int_get_good_color(xvar,color);
   XChangeGC(xvar->display,win->gc,GCForeground,&xgcv);
   XDrawString(xvar->display,win->window,win->gc,x,y,string,strlen(string));
   if (xvar->do_flush)
     XFlush(xvar->display);
}
