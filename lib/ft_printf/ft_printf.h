/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:45:51 by sbansacc          #+#    #+#             */
/*   Updated: 2024/06/04 23:18:48 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "../libft/libft.h"

int	hexalen(unsigned long long hex);
int	print_char(int argument);
int	print_str(char *argument);
int	print_hexa(void *argument);
int	print_nbr(int argument);
int	print_uint( unsigned int argument);
int	print_lowhexa(unsigned int argument);
int	print_uphexa(unsigned int argument);
int	ft_printf(const char *format, ...);

#endif