/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:02:08 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/21 02:51:57 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf_bonus.h"

int	print_percent_bonus(t_flags flags)
{
	int	printed_char;

	printed_char = 0;
	if (print_width(flags, 1, &printed_char) == (-1))
		return (-1);
	if (write(1, "%", 1) == (-1))
		return (-1);
	printed_char++;
	if (print_minus(flags, &printed_char) == (-1))
		return (-1);
	return (printed_char);
}
