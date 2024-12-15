/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:35:46 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/21 03:56:50 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

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

int	print_hexa_bonus(void *argument, t_flags flags)
{
	int					printed_char;
	unsigned long long	addr;
	int					len;

	addr = (unsigned long long)argument;
	len = hexalen(addr);
	printed_char = 0;
	if (!flags.has_minus && flags.width)
	{
		while (printed_char < (flags.width - len - 2))
		{
			if (write(1, " ", 1) == (-1))
				return (-1);
			printed_char++;
		}
	}
	if (write(1, "0x", 2) == (-1))
		return (-1);
	if (ft_puthexa(addr) == (-1))
		return (-1);
	printed_char += len + 2;
	if (print_minus(flags, &printed_char) == (-1))
		return (-1);
	return (printed_char);
}
