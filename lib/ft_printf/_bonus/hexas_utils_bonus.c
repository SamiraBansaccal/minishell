/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexas_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 07:41:53 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/21 03:53:09 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

int	hexalen(unsigned long long hex)
{
	int	len;

	if (hex == 0)
		len = 1;
	else
		len = 0;
	while (hex > 0)
	{
		len++;
		hex /= 16;
	}
	return (len);
}

int	print_minus(t_flags flags, int *printed_char)
{
	if (flags.has_minus && flags.width)
	{
		while (*printed_char < flags.width)
		{
			if (write(1, " ", 1) == (-1))
				return (-1);
			(*printed_char)++;
		}
	}
	return (0);
}

int	print_width(t_flags flags, int len, int *printed_char)
{
	if (!flags.has_minus && !flags.has_zero && flags.width)
	{
		while (*printed_char < (flags.width - len))
		{
			if (write(1, " ", 1) == (-1))
				return (-1);
			(*printed_char)++;
		}
	}
	return (0);
}

int	print_precision(t_flags flags, int len, int *printed_char)
{
	while (flags.precision > len)
	{
		if (write(1, "0", 1) == (-1))
			return (-1);
		(*printed_char)++;
		len++;
	}
	return (0);
}

void	ajust_len(int argument, t_flags *flags, int *len)
{
	if (argument < 0 && (*flags).has_dot)
	{
		(*flags).has_dot = 0;
		(*flags).has_zero = 0;
	}
	if ((*flags).precision && (*flags).precision > *len)
		*len = (*flags).precision;
	if ((*flags).has_hash && argument != 0)
		*len += 2;
	if (argument == 0 && (*flags).has_dot && !(*flags).precision)
		*len = 0;
}
