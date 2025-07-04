/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:32:23 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 23:04:48 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../stdio/ft_stdio.h"
#include "../stdlib/ft_stdlib.h"

int	ft_is_negative(int x)
{
	int	mask;

	mask = x >> (sizeof(int) * 8 - 1);
	return (mask & 1);
}

//int main(int argc, char **argv)
//{
//    if (argc != 2)
//        return 1;
//    int x = atoi(argv[1]);
//    printf("%d is %snegative\n", x, ft_is_negative(x) ? "" : "not ");
//    return 0;
//}