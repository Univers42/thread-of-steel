/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_flush_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:49:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:49:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

int	mlx_flush_event(t_xvar *xvar)
{
  XEvent	ev;

  while (XPending(xvar->display))
  {
     XNextEvent(xvar->display,&ev);
  }
}
