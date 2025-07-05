/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:47:01 by dlesieur          #+#    #+#             */
/*   Updated: 2025/07/05 19:09:56 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include "parser.h"

int should_skip(char c, t_state flags)
{
	if ((flags & TRIM_SPACES) && (c == ' ' || c == '\t' || c == '\n' || c == '\r'))
		return (1);
	if ((flags & TRIM_NUMS) && (c >= '0' && c <= '9'))
		return (1);
	if ((flags & TRIM_RADIX) && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
		return (1);
	return (0);
}

void ft_trim(t_addr *ptr, t_state flags)
{
	while (*(char *)*ptr && should_skip(*(char *)*ptr, flags))
		*ptr = (char *)*ptr + 1;
}

int extract_sign(t_addr *ptr)
{
	if (*(char *)*ptr == '-')
	{
		*ptr = (char *)*ptr + 1;
		return (1);
	}
	if (*(char *)*ptr == '+')
		*ptr = (char *)*ptr + 1;
	return (0);
}

int cumul_value(t_addr *ptr, t_addr target)
{
	int *val = (int *)target;
	int negative = extract_sign(ptr);
	
	*val = 0;
	while (*(char *)*ptr >= '0' && *(char *)*ptr <= '9')
	{
		*val = *val * 10 + (*(char *)*ptr - '0');
		*ptr = (char *)*ptr + 1;
	}
	if (negative)
		*val = -*val;
	return (*val);
}

int extract_hex(t_addr *ptr, t_addr result)
{
	int *color = (int *)result;
	char c;
	int digit;
	
	*color = 0;
	if (*(char *)*ptr == '0' && (*(char *)(*ptr + 1) == 'x' || *(char *)(*ptr + 1) == 'X'))
	{
		*ptr = (char *)*ptr + 2; // Skip "0x"
		while (*(char *)*ptr)
		{
			c = *(char *)*ptr;
			if (c >= '0' && c <= '9')
				digit = c - '0';
			else if (c >= 'a' && c <= 'f')
				digit = c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				digit = c - 'A' + 10;
			else
				break;
			*color = *color * 16 + digit;
			*ptr = (char *)*ptr + 1;
		}
	}
	else
		*color = DEFAULT_WHITE;
	return (*color);
}

void advance_ptr(t_addr *ptr, char delimiter)
{
	while (*(char *)*ptr && *(char *)*ptr != delimiter)
		*ptr = (char *)*ptr + 1;
	if (*(char *)*ptr == delimiter)
		*ptr = (char *)*ptr + 1;
}