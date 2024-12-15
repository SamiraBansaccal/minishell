/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:36:03 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/20 03:56:27 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

int	print_zero(t_flags flags, int len, int *printed_char)
{
	if (!flags.has_minus && flags.has_zero && flags.width && flags.has_dot)
	{
		while (*printed_char < (flags.width - len))
		{
			if (write(1, " ", 1) == (-1))
				return (-1);
			(*printed_char)++;
		}
	}
	if (!flags.has_minus && flags.has_zero && flags.width && !flags.has_dot)
	{
		while (*printed_char < (flags.width - len))
		{
			if (write(1, "0", 1) == (-1))
				return (-1);
			(*printed_char)++;
		}
	}
	return (0);
}

int	uintlen(unsigned int nbr)
{
	int	len;

	if (nbr == 0)
		len = 1;
	else
		len = 0;
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

int	print_uint_bonus(unsigned int argument, t_flags flags)
{
	int				printed_char;
	int				len;

	printed_char = 0;
	len = uintlen(argument);
	ajust_len(argument, &flags, &len);
	if (print_width(flags, len, &printed_char) == (-1))
		return (-1);
	if (print_zero(flags, len, &printed_char) == (-1))
		return (-1);
	len = uintlen(argument);
	if (print_precision(flags, len, &printed_char) == (-1))
		return (-1);
	if (!(argument == 0 && flags.has_dot && !flags.precision))
	{
		if (ft_putnbr(argument, len) == (-1))
			return (-1);
		printed_char += len;
	}
	if (print_minus(flags, &printed_char) == (-1))
		return (-1);
	return (printed_char);
}
