/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:39:28 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/21 04:07:19 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

int	print_format(const char format, va_list arg_list, t_flags flags)
{
	if (format == 'c')
		return (print_char_bonus(va_arg(arg_list, int), flags));
	else if (format == 's')
		return (print_str_bonus(va_arg(arg_list, char *), flags));
	else if (format == 'p')
		return (print_hexa_bonus(va_arg(arg_list, void *), flags));
	else if (format == 'd' || format == 'i')
		return (print_nbr_bonus(va_arg(arg_list, int), flags));
	else if (format == 'u')
		return (print_uint_bonus(va_arg(arg_list, unsigned int), flags));
	else if (format == 'x')
		return (print_lowhexa_bonus(va_arg(arg_list, int), flags));
	else if (format == 'X')
		return (print_uphexa_bonus(va_arg(arg_list, int), flags));
	else if (format == '%')
		return (print_percent_bonus(flags));
	else
		return (0);
}

int	get_nbr(const char *str, int *i)
{
	int	nbr;

	nbr = 0;
	while (ft_isdigit(str[*i]))
	{
		if (nbr > 0)
			nbr *= 10;
		nbr += (str[*i] - '0');
		(*i)++;
	}
	return (nbr);
}

int	check_flags(const char *str, t_flags *flags, int i)
{
	while (ft_strchr("cspdiuxX%", str[i]) == NULL)
	{
		if (str[i] == '.')
			flags->has_dot = 1;
		else if (str[i] == '0')
			flags->has_zero = 1;
		else if (str[i] == '#')
			flags->has_hash = 1;
		else if (str[i] == ' ')
			flags->has_space = 1;
		else if (str[i] == '+')
			flags->has_plus = 1;
		else if (str[i] == '-')
			flags->has_minus = 1;
		if (ft_isdigit(str[i]) && str[i] != 0)
		{
			if (str[i - 1] == '.')
				flags->precision = get_nbr(str, &i);
			else
				flags->width = get_nbr(str, &i);
		}
		else
			i++;
	}
	return (i);
}

int	ft_parse(const char *str, va_list argument_list, int *printed_char,
	t_flags flags)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			ft_memset(&flags, 0, sizeof(flags));
			if (ft_strchr("cspdiuxX%", str[i]) == NULL)
				i = check_flags(str, &flags, i);
			*printed_char += print_format(str[i], argument_list, flags);
			if (*printed_char == (-1))
				return (*printed_char);
		}
		else
		{
			if (write(1, &str[i], 1) == (-1))
				return (-1);
			(*printed_char)++;
		}
		i++;
	}
	return (*printed_char);
}

int	ft_printf(const char *str, ...)
{
	int		printed_char;
	va_list	argument_list;
	t_flags	flags;

	printed_char = 0;
	ft_memset(&flags, 0, sizeof(flags));
	if (!str)
		return (0);
	va_start(argument_list, str);
	printed_char = ft_parse(str, argument_list, &printed_char, flags);
	va_end(argument_list);
	return (printed_char);
}
