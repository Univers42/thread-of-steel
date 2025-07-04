/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:42:22 by dlesieur          #+#    #+#             */
/*   Updated: 2025/04/27 17:27:10 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * ft_swap - Swap the contents of two memory areas of any type.
 *
 * @param a:    Pointer to the first memory area.
 * @param b:    Pointer to the second memory area.
 * @param size: Number of bytes to swap 
 * (use sizeof(type) for the type you want to swap).
 *
 * This function swaps the contents of the memory pointed to by @a and @b,
 * byte by byte, using bitwise XOR operations. It works for any data type,
 * including char, int, float, double, and structs, as long as you provide
 * the correct size.
 *
 * Example usage:
 *     int x = 42, y = 24;
 *     ft_swap(&x, &y, sizeof(int));
 *     // Now x == 24, y == 42
 *
 *     char c1 = 'A', c2 = 'B';
 *     ft_swap(&c1, &c2, sizeof(char));
 *     // Now c1 == 'B', c2 == 'A'
 *
 * Note: If @a and @b point to the same memory, the function does nothing.
 */
void	ft_swap(void *a, void *b, size_t size)
{
	unsigned char	*pa;
	unsigned char	*pb;

	pa = (unsigned char *)a;
	pb = (unsigned char *)b;
	if (a == b)
		return ;
	while (size --)
	{
		(*pa ^= *pb);
		(*pb ^= *pa);
		(*pa ^= *pb);
		pa++;
		pb++;
	}
}

//int main(void)
//{
//    // Example 1: Swap integers
//    int x = 42, y = 24;
//    printf("Before swap: x = %d, y = %d\n", x, y);
//    ft_swap(&x, &y, sizeof(int));
//    printf("After swap:  x = %d, y = %d\n\n", x, y);
//
//    // Example 2: Swap characters
//    char c1 = 'A', c2 = 'B';
//    printf("Before swap: c1 = %c, c2 = %c\n", c1, c2);
//    ft_swap(&c1, &c2, sizeof(char));
//    printf("After swap:  c1 = %c, c2 = %c\n\n", c1, c2);
//
//    // Example 3: Swap doubles
//    double d1 = 3.14, d2 = 2.71;
//    printf("Before swap: d1 = %f, d2 = %f\n", d1, d2);
//    ft_swap(&d1, &d2, sizeof(double));
//    printf("After swap:  d1 = %f, d2 = %f\n\n", d1, d2);
//
//    // Example 4: Swap strings (pointers, not contents)
//    char *s1 = "Hello";
//    char *s2 = "World";
//    printf("Before swap: s1 = %s, s2 = %s\n", s1, s2);
//    ft_swap(&s1, &s2, sizeof(char *));
//    printf("After swap:  s1 = %s, s2 = %s\n", s1, s2);
//
//    return 0;
//}