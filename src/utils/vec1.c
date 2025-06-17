/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 16:05:18 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

t_vec2 vec2_add(t_vec2 a, t_vec2 b)
{
    t_vec2 result;
    
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    
    return (result);
}

t_vec2 vec2_subtract(t_vec2 a, t_vec2 b)
{
    t_vec2 result;
    
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    
    return (result);
}

t_vec2 vec2_scale(t_vec2 v, float scale)
{
    t_vec2 result;
    
    result.x = v.x * scale;
    result.y = v.y * scale;
    
    return (result);
}

float vec2_dot(t_vec2 a, t_vec2 b)
{
    return (a.x * b.x + a.y * b.y);
}

float vec2_length(t_vec2 v)
{
    return (fast_sqrt(v.x * v.x + v.y * v.y));
}

t_vec2 vec2_normalize(t_vec2 v)
{
    float length = vec2_length(v);
    t_vec2 result;
    
    if (length == 0.0f)
    {
        result.x = 0.0f;
        result.y = 0.0f;
        return (result);
    }
    
    result.x = v.x / length;
    result.y = v.y / length;
    
    return (result);
}