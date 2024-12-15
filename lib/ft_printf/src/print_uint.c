/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:36:03 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/15 19:02:19 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

int	print_uint(unsigned int argument)
{
	char	digit;
	int		nbrlen;

	nbrlen = 1;
	if (argument > 9)
	{
		if (print_uint(argument / 10) == (-1))
			return (-1);
		if (print_uint(argument % 10) == (-1))
			return (-1);
	}
	if (argument <= 9)
	{
		digit = argument + '0';
		if (write(1, &digit, 1) == (-1))
			return (-1);
	}
	while (argument > 9)
	{
		argument /= 10;
		nbrlen++;
	}
	return (nbrlen);
}
