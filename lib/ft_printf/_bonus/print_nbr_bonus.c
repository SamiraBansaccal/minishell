/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:35:53 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/20 05:16:14 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

int	print_sign(t_flags flags, int *len, long *nbr, int **printed_char)
{
	if (*nbr < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		(**printed_char)++;
		*nbr *= (-1);
		if (flags.has_plus)
			(*len)--;
	}
	else if (*nbr >= 0 && flags.has_plus)
	{
		if (write(1, "+", 1) == -1)
			return (-1);
		(**printed_char)++;
		(*len)--;
	}
	return (0);
}

int	print_signed_zero(t_flags flags, int len, long *nbr, int *printed_char)
{
	if (flags.has_plus)
		len++;
	if (!flags.has_minus && flags.has_zero && flags.width && flags.has_dot)
	{
		while (*printed_char < (flags.width - len))
		{
			if (write(1, " ", 1) == (-1))
				return (-1);
			(*printed_char)++;
		}
	}
	if (print_sign(flags, &len, nbr, &printed_char) == (-1))
		return (-1);
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

int	nbrlen(long nbr)
{
	int	len;

	if (nbr == 0)
		len = 1;
	else
		len = 0;
	if (nbr < 0)
		nbr *= (-1);
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

int	print_nbr_bonus(int argument, t_flags flags)
{
	int				printed_char;
	int				len;
	long			nbr;

	nbr = argument;
	printed_char = 0;
	len = nbrlen(nbr);
	ajust_len(nbr, &flags, &len);
	if (print_nbr_width(flags, len, &printed_char, nbr) == (-1))
		return (-1);
	if (print_signed_zero(flags, len, &nbr, &printed_char) == (-1))
		return (-1);
	len = nbrlen(nbr);
	if (print_precision(flags, len, &printed_char) == (-1))
		return (-1);
	if (!(nbr == 0 && flags.has_dot && !flags.precision))
	{
		if (ft_putnbr(nbr, len) == (-1))
			return (-1);
		printed_char += len;
	}
	if (print_minus(flags, &printed_char) == (-1))
		return (-1);
	return (printed_char);
}
