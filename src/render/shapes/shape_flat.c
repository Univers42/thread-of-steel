/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_flat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:30:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:50:11 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"

t_vec3 shape_flat_transform(t_point point, t_shape_context context)
{
    t_vec3 result;
    
    (void)context; // No transformation needed for flat shape
    
    result.x = (float)point.x;
    result.y = (float)point.y;
    result.z = (float)point.z;
    
    return (result);
}
