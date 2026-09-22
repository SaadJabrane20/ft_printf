/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sajabran <sajabran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:55:42 by sajabran          #+#    #+#             */
/*   Updated: 2026/09/22 19:50:57 by sajabran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int			ft_putchar(char c);
int			ft_putnbr(int n);
size_t		ft_putstr(char *s);
int			ft_put_hex(unsigned int n, const char *base);
const char	*check_base(char c);
int			ft_print_pointer(void *ptr);
int			parser(char format, va_list args);
int			ft_printf(const char *format, ...);
int			ft_putnbr_unsigned(unsigned int n);
#endif
