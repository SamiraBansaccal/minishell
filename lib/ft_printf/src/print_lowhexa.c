/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lowhexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:35:50 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/14 03:38:37 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

int	ft_putlowhexa(unsigned long long hex)
{
	char	*base;

	base = "0123456789abcdef";
	if (hex > 15)
		if (ft_putlowhexa(hex / 16))
			return (-1);
	if (write(1, &base[hex % 16], 1) == (-1))
		return (-1);
	else
		return (0);
}

int	print_lowhexa(unsigned int argument)
{
	int					printed_char;
	unsigned long long	hex;

	hex = (unsigned long long)argument;
	printed_char = 0;
	if (hex == 0)
	{
		if (write(1, "0", 1) == (-1))
			return (-1);
		printed_char++;
	}
	else
	{
		if (ft_putlowhexa(hex) == (-1))
			return (-1);
		printed_char += hexalen(hex);
	}
	return (printed_char);
}
