/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:35:42 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/14 06:21:52 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

int	print_char_bonus(int argument, t_flags flags)
{
	int	printed_char;

	printed_char = 1;
	if (!flags.has_minus)
	{
		while (flags.width > printed_char)
		{
			if (write(1, " ", 1) == (-1))
				return (-1);
			printed_char++;
		}
	}
	if (write(1, &argument, 1) == (-1))
		return (-1);
	if (flags.has_minus)
	{
		while (flags.width > printed_char)
		{
			if (write(1, " ", 1) == (-1))
				return (-1);
			printed_char++;
		}
	}
	return (printed_char);
}
