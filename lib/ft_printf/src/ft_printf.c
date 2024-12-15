/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:39:28 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/14 07:03:16 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

int	print_format(const char format, va_list argument_list)
{
	if (format == 'c')
		return (print_char(va_arg(argument_list, int)));
	else if (format == 's')
		return (print_str(va_arg(argument_list, char *)));
	else if (format == 'p')
		return (print_hexa(va_arg(argument_list, void *)));
	else if (format == 'd' || format == 'i')
		return (print_nbr(va_arg(argument_list, int)));
	else if (format == 'u')
		return (print_uint(va_arg(argument_list, unsigned int)));
	else if (format == 'x')
		return (print_lowhexa(va_arg(argument_list, unsigned int)));
	else if (format == 'X')
		return (print_uphexa(va_arg(argument_list, unsigned int)));
	else if (format == '%')
		return (write(1, "%", 1));
	else
		return (0);
}

int	ft_parse(const char *str, va_list argument_list)
{
	int		i;
	int		printed_char;

	i = 0;
	printed_char = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			printed_char += print_format(str[i], argument_list);
			if (printed_char == (-1))
				return (printed_char);
		}
		else
		{
			if (write(1, &str[i], 1) == (-1))
				return (-1);
			printed_char++;
		}
		i++;
	}
	return (printed_char);
}

int	ft_printf(const char *str, ...)
{
	int		printed_char;
	va_list	argument_list;

	if (!str)
		return (0);
	va_start(argument_list, str);
	printed_char = ft_parse(str, argument_list);
	va_end(argument_list);
	return (printed_char);
}
