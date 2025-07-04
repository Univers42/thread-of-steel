/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_banner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlesieur <dlesieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:00:00 by dlesieur          #+#    #+#             */
/*   Updated: 2025/06/04 14:33:39 by dlesieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_render.h"

static void	print_border(int width, char corner, char line)
{
	int	i;

	printf("%c", corner);
	i = 0;
	while (i < width - 2)
	{
		printf("%c", line);
		i++;
	}
	printf("%c\n", corner);
}

static void	print_centered(const char *text, int width)
{
	int	text_len;
	int	padding;
	int	i;

	if (!text)
		return ;
	text_len = strlen(text);
	if (text_len > width - 4)
		text_len = width - 4;
	padding = (width - text_len) / 2;
	i = 0;
	while (i < padding)
	{
		printf(" ");
		i++;
	}
	printf("%s\n", text);
}

void	ft_print_banner(const char *title, const char *subtitle,
			t_banner_style style)
{
	int		width;
	char	corner;
	char	line;

	if (!title)
		return ;
	width = ft_get_terminal_width();
	if (width > 80)
		width = 80;
	corner = '+';
	line = '-';
	if (style == BANNER_DOUBLE)
	{
		corner = '#';
		line = '=';
	}
	print_border(width, corner, line);
	print_centered(title, width);
	if (subtitle)
		print_centered(subtitle, width);
	print_border(width, corner, line);
}

void	ft_print_boxed(const char *text)
{
	int	width;
	int	text_len;
	int	padding;
	int	i;

	if (!text)
		return ;
	width = ft_get_terminal_width();
	text_len = strlen(text);
	if (text_len > width - 4)
		text_len = width - 4;
	padding = (width - text_len - 2) / 2;
	print_border(width, '+', '-');
	printf("|");
	i = -1;
	while (++i < padding)
		printf(" ");
	printf("%.*s", text_len, text);
	i = -1;
	while (++i < width - text_len - padding - 2)
		printf(" ");
	printf("|\n");
	print_border(width, '+', '-');
}
