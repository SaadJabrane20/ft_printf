/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 15:14:43 by sajabran          #+#    #+#             */
/*   Updated: 2026/09/21 21:43:57 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	parser(const char *format, va_list args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
			{
				count += ft_putchar('%');
    			break;
			}
			else if (format[i] == 'c')
				count += ft_putchar(va_arg(args, int));
			else if (format[i] == 's')
				count += ft_putstr(va_arg(args, char *));
			else if (format[i] == 'd')
				count += ft_putnbr(va_arg(args, int));
			else if (format[i] == 'x' || format[i] == 'X')
				count += ft_put_hex(va_arg(args, unsigned int), check_base(format[i]));
			else if (format[i] == 'p')
				count += ft_print_pointer(va_arg(args, void *));
			else if (format[i] == 'u')
				count += ft_putnbr_unsigned(va_arg(args, unsigned int));
			else if (format[i] == '%')
				count += ft_putchar('%');
			else
			{
				count += ft_putchar('%');
				count += ft_putchar(format[i]);
			}
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	return (count);
}
