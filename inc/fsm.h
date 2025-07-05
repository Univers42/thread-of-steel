/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:08:47 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/05 21:44:36 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSM_H
# define FSM_H

// FSM -like to create the mini super trim
// due to need to skip different string pattern
typedef enum s_state
{
	TRIM_RADIX = (1 << 0),
	TRIM_SPACES = (1 << 1),
	TRIM_NUMS = (1 << 2),
}			t_state;

#endif