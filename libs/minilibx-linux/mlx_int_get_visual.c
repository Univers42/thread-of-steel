/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_get_visual.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:39:16 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:39:25 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

int		mlx_int_get_visual(t_xvar *xvar)
{
  XVisualInfo	*vi;
  XVisualInfo	template;
  int		nb_item;

  xvar->private_cmap = 0;
  xvar->visual = DefaultVisual(xvar->display,xvar->screen);
  if (xvar->visual->class == TrueColor)
    return (0);
  template.class = TrueColor;
  template.depth = xvar->depth;
  if (!(vi = XGetVisualInfo(xvar->display,VisualDepthMask|VisualClassMask,
			    &template,&nb_item)) )
    return (-1);
  xvar->visual = vi->visual;
  xvar->private_cmap = 1;
  return (0);
}
