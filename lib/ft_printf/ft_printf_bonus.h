/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:45:51 by sbansacc          #+#    #+#             */
/*   Updated: 2024/07/29 01:30:51 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct s_flags
{
	int	has_minus;
	int	has_zero;
	int	has_dot;
	int	has_space;
	int	has_plus;
	int	has_hash;
	int	width;
	int	precision;
}	t_flags;

int		ft_putnbr(unsigned int argument, int len_max);
int		print_nbr_width(t_flags flags, int len, int *printed_char, long nbr);
int		print_minus(t_flags flags, int *printed_char);
int		print_width(t_flags flags, int len, int *printed_char);
int		print_precision(t_flags flags, int len, int *printed_char);
void	ajust_len(int argument, t_flags *flags, int *len);
int		print_char_bonus(int argument, t_flags flags);
int		print_str_bonus(char *argument, t_flags flags);
int		hexalen(unsigned long long hex);
int		print_hexa_bonus(void *argument, t_flags flags);
int		print_nbr_bonus(int argument, t_flags flags);
int		print_uint_bonus(unsigned int argument, t_flags flags);
int		print_lowhexa_bonus(int argument, t_flags flags);
int		print_uphexa_bonus(int argument, t_flags flags);
int		print_percent_bonus(t_flags flags);
int		ft_printf(const char *format, ...);

#endif