/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrs_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 07:42:02 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/20 05:01:42 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

int	ft_putnbr(unsigned int argument, int len_max)
{
	char	*base;

	if (argument == 0)
	{
		if (write(1, "0", 1) == (-1))
			return (-1);
		return (0);
	}
	base = "0123456789";
	if (argument > 9 && len_max > 0)
	{
		len_max--;
		if (ft_putnbr(argument / 10, len_max) == (-1))
			return (-1);
	}
	if (write(1, &base[argument % 10], 1) == (-1))
		return (-1);
	else
		return (0);
}

int	print_nbr_width(t_flags flags, int len, int *printed_char, long nbr)
{
	if (nbr < 0 || flags.has_plus)
		len++;
	if (nbr >= 0 && flags.has_space)
	{
		if (write(1, " ", 1) == (-1))
			return (-1);
		(*printed_char)++;
	}
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
