/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:35:46 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/14 03:38:32 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

int	hexalen(unsigned long long hex)
{
	int	len;

	len = 0;
	while (hex > 0)
	{
		len++;
		hex /= 16;
	}
	return (len);
}

int	ft_puthexa(unsigned long long addr)
{
	char	*base;

	base = "0123456789abcdef";
	if (addr > 15)
		if (ft_puthexa(addr / 16) == (-1))
			return (-1);
	if (write(1, &base[addr % 16], 1) == (-1))
		return (-1);
	else
		return (0);
}

int	print_hexa(void *argument)
{
	int					printed_char;
	unsigned long long	addr;
	int					len;

	addr = (unsigned long long)argument;
	len = hexalen(addr);
	printed_char = 0;
	if (!addr || !argument)
		return (write(1, "0x0", 3));
	if (write(1, "0x", 2) == (-1))
		return (-1);
	printed_char += 2;
	if (ft_puthexa(addr) == (-1))
		return (-1);
	printed_char += len;
	return (printed_char);
}
