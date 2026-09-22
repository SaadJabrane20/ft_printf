/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 15:10:55 by sajabran          #+#    #+#             */
/*   Updated: 2026/09/22 19:45:41 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = -1;
	count = 0;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
			{
				count += ft_putchar('%');
				break ;
			}
			count += parser(format[i], args);
		}
		else
			count += ft_putchar(format[i]);
	}
	return (count);
}
