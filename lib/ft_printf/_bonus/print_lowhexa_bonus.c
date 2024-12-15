/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lowhexa_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:35:50 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/21 03:51:20 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

int	ft_putlowhexa(unsigned int hex, int len_max)
{
	char	*base;

	if (hex == 0)
	{
		if (write(1, "0", 1) == (-1))
			return (-1);
		return (0);
	}
	base = "0123456789abcdef";
	if (hex > 15 && len_max > 0)
	{
		len_max--;
		if (ft_putlowhexa(hex / 16, len_max) == (-1))
			return (-1);
	}
	if (write(1, &base[hex % 16], 1) == (-1))
		return (-1);
	else
		return (0);
}

int	print_lowhash(t_flags flags, unsigned int hex, int **printed_char)
{
	if (flags.has_hash && hex != 0)
	{
		if (write(1, "0x", 2) == (-1))
			return (-1);
		**printed_char += 2;
	}
	return (0);
}

int	print_zero_lowhash(t_flags flags, int len, unsigned int hex,
	int *printed_char)
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
	if (print_lowhash(flags, hex, &printed_char) == (-1))
		return (-1);
	if (flags.has_hash && hex != 0)
		len -= 2;
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

int	print_lowhexa_bonus(int argument, t_flags flags)
{
	int				printed_char;
	unsigned int	hex;
	int				len;

	printed_char = 0;
	hex = (unsigned int)argument;
	len = hexalen(hex);
	ajust_len(argument, &flags, &len);
	if (print_width(flags, len, &printed_char) == (-1))
		return (-1);
	if (print_zero_lowhash(flags, len, hex, &printed_char) == (-1))
		return (-1);
	len = hexalen(hex);
	if (print_precision(flags, len, &printed_char) == (-1))
		return (-1);
	if (!(hex == 0 && flags.has_dot && !flags.precision))
	{
		if (ft_putlowhexa(hex, len) == (-1))
			return (-1);
		printed_char += len;
	}
	if (print_minus(flags, &printed_char) == (-1))
		return (-1);
	return (printed_char);
}
