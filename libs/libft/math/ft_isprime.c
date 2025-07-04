/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:44:43 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/28 23:07:22 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_is_prime(int x)
{
	int	i;

	if (x < 2)
		return (0);
	i = 2;
	while ((i * i) <= x)
	{
		if (!(x % i))
			return (0);
		i++;
	}
	return (1);
}

//int main(int argc, char **argv)
//{
//    if (argc != 2)
//        return 1;
//    int x = atoi(argv[1]);
//    printf("%d is %sprime\n", x, ft_is_prime(x) ? "" : "not ");
//    return 0;
//}