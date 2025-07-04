/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_power_of_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:18:49 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 23:05:42 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../stdio/ft_stdio.h"
#include "../stdlib/ft_stdlib.h"

int	ft_is_power2(int x)
{
	return ((x > 0) && ((x & (x - 1)) == 0));
}

//#include <stdio.h>
//#include <stdlib.h>
//
//int main(int argc, char **argv)
//{
//    if (argc != 2)
//        return 1;
//    int x = atoi(argv[1]);
//    printf("%d is %sa power of 2\n", x, ft_is_power2(x) ? "" : "not ");
//    return 0;
//}