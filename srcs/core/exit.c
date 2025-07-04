/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:02 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/04 17:33:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void free_maps(t_map *map)
{
    if (!map || !map->map)
        return ;
    while (map->rows > 0)
    {
        free(map->map[--map->rows]);
        map->map[map->rows] = NULL;
    }
    free(map->map);
    map->map = NULL;
}