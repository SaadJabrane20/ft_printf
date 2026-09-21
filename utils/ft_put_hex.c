/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 15:28:31 by sajabran          #+#    #+#             */
/*   Updated: 2026/09/21 18:48:57 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_put_hex(unsigned int n, const char *base)
{
	int		count;

	count = 0;
	if (n >= 16)
		count = count + ft_put_hex(n / 16, base);
	ft_putchar(base[n % 16]);
	count++;
	return (count);
}
