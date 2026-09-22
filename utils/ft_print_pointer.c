/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 18:40:25 by sajabran          #+#    #+#             */
/*   Updated: 2026/09/22 19:46:12 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	put_hex(unsigned long n, const char *base)
{
	int		count;

	count = 0;
	if (n >= 16)
		count = count + put_hex(n / 16, base);
	ft_putchar(base[n % 16]);
	count++;
	return (count);
}

int	ft_print_pointer(void *ptr)
{
	int	count;

	count = 0;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	count = 2;
	count += put_hex((unsigned long)ptr, "0123456789abcdef");
	return (count);
}
