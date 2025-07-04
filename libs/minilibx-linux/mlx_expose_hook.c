/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_expose_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:49:07 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:49:08 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"mlx_int.h"

int		mlx_expose_hook(t_win_list *win,int (*funct)(),void *param)
{
  win->hooks[Expose].hook = funct;
  win->hooks[Expose].param = param;
  win->hooks[Expose].mask = ExposureMask;
}
