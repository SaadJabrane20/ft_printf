/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 15:14:43 by sajabran          #+#    #+#             */
/*   Updated: 2026/09/22 19:45:21 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	parser(char c, va_list args)
{
	int	ret;

	if (c == 'c')
		ret = ft_putchar(va_arg(args, int));
	else if (c == 's')
		ret = ft_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		ret = ft_putnbr(va_arg(args, int));
	else if (c == 'x' || c == 'X')
		ret = ft_put_hex(va_arg(args, unsigned int), check_base(c));
	else if (c == 'p')
		ret = ft_print_pointer(va_arg(args, void *));
	else if (c == 'u')
		ret = ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (c == '%')
		ret = ft_putchar('%');
	else
	{
		ret = ft_putchar('%');
		ret += ft_putchar(c);
	}
	return (ret);
}
