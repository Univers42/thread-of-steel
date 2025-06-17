/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:20:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/17 15:19:15 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void matrix_multiply_3x3(float a[3][3], float b[3][3], float result[3][3])
{
    int i, j, k;
    
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            result[i][j] = 0.0f;
            for (k = 0; k < 3; k++)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void matrix_vector_multiply_3x3(float matrix[3][3], t_vec3 vec, t_vec3 *result)
{
    if (!result)
        return;
    
    result->x = matrix[0][0] * vec.x + matrix[0][1] * vec.y + matrix[0][2] * vec.z;
    result->y = matrix[1][0] * vec.x + matrix[1][1] * vec.y + matrix[1][2] * vec.z;
    result->z = matrix[2][0] * vec.x + matrix[2][1] * vec.y + matrix[2][2] * vec.z;
}

void matrix_identity_3x3(float matrix[3][3])
{
    int i, j;
    
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (i == j)
                matrix[i][j] = 1.0f;
            else
                matrix[i][j] = 0.0f;
        }
    }
}
