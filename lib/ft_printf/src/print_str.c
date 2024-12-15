/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:36:00 by sbansacc          #+#    #+#             */
/*   Updated: 2024/04/14 03:38:45 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

int	print_str(char *argument)
{
	int	printed_char;
	int	i;

	if (!argument)
		return (write(1, "(null)", 6));
	printed_char = 0;
	i = 0;
	while (argument[i])
	{
		if (write(1, &argument[i], 1) == (-1))
			return (-1);
		i++;
		printed_char++;
	}
	return (printed_char);
}
