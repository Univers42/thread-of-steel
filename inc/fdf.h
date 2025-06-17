/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:27:17 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:20:12 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* ************************************************************************** */
/*                          MAIN FDF HEADER                                  */
/* ************************************************************************** */

// Include organized headers in dependency order
# include "fdf_config.h"
# include "fdf_internal.h" 
# include "fdf_public.h"
#include "fdf_private.h"

// Legacy compatibility - redefine old constants for existing code
# define ESC_KEY        KEY_ESC
# define W_KEY          KEY_W
# define A_KEY          KEY_A
# define S_KEY          KEY_S
# define D_KEY          KEY_D
# define Q_KEY          KEY_Q
# define E_KEY          KEY_E
# define R_KEY          KEY_R
# define T_KEY          KEY_T
# define UP_KEY         KEY_UP
# define DOWN_KEY       KEY_DOWN
# define LEFT_KEY       KEY_LEFT
# define RIGHT_KEY      KEY_RIGHT
# define PLUS_KEY       KEY_PLUS
# define MINUS_KEY      KEY_MINUS
# define SPACE_KEY      KEY_SPACE
# define TAB_KEY        KEY_TAB
# define ALT_L          KEY_ALT_L
# define ALT_R          KEY_ALT_R

// Legacy compatibility for mouse buttons
# define MOUSE_LEFT     MOUSE_LEFT_BUTTON
# define MOUSE_RIGHT    MOUSE_RIGHT_BUTTON
# define MOUSE_WHEEL_UP MOUSE_SCROLL_UP
# define MOUSE_WHEEL_DOWN MOUSE_SCROLL_DOWN

// Legacy compatibility for shapes
# define SHAPE_FLAT     SHAPE_TYPE_FLAT
# define SHAPE_SPHERE   SHAPE_TYPE_SPHERE


#endif
