/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:02:29 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:19:14 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    t_vec3 result;
    
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    
    return (result);
}

t_vec3 vec3_subtract(t_vec3 a, t_vec3 b)
{
    t_vec3 result;
    
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    
    return (result);
}

t_vec3 vec3_scale(t_vec3 v, float scale)
{
    t_vec3 result;
    
    result.x = v.x * scale;
    result.y = v.y * scale;
    result.z = v.z * scale;
    
    return (result);
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    t_vec3 result;
    
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    
    return (result);
}

float vec3_dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float vec3_length(t_vec3 v)
{
    return (fast_sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3 vec3_normalize(t_vec3 v)
{
    float length = vec3_length(v);
    t_vec3 result;
    
    if (length == 0.0f)
    {
        result.x = 0.0f;
        result.y = 0.0f;
        result.z = 0.0f;
        return (result);
    }
    
    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;
    
    return (result);
}

