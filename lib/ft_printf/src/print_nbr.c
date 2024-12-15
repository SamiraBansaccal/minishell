/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:35:53 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/21 04:13:02 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

int	nbrlen(int n)
{
	int			nbrlen;

	nbrlen = 1;
	while (n > 9)
	{
		n /= 10;
		nbrlen++;
	}
	return (nbrlen);
}

int	print_nbr(int argument)
{
	char	*base;
	int		sign;

	sign = 0;
	if (argument == -2147483648)
		return (write(1, "-2147483648", 11));
	if (argument < 0)
	{
		if (write(1, "-", 1) == (-1))
			return (-1);
		argument *= (-1);
		sign = 1;
	}
	base = "0123456789";
	if (argument > 9)
		if (print_nbr(argument / 10) == (-1))
			return (-1);
	if (write(1, &base[argument % 10], 1) == (-1))
		return (-1);
	else
		return (nbrlen(argument) + sign);
}
