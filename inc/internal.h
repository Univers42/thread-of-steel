/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:40:55 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 18:42:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

/**
 * The key codes in this projects are integeres, we will need to hold them
 through variables that we will call. this is simply a collection of
 variable for configurations sake... 
 */
typedef enum s_hook_key
{
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_ESC = 53,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_E = 14,
	KEY_SPACE = 49,
	KEY_TAB = 48,
	KEY_PLUS = 24,
	KEY_MINUS = 27
}			t_hook_key;

#endif