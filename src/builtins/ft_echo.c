/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:14:32 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/15 19:03:28 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_args(char **args, int i, int fd_outfile)
{
	while (args[i])
	{
		write(fd_outfile, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(fd_outfile, " ", 1);
	}
}

int	check_flag_n(char **args, int *newline)
{
	int	i;
	int	j;

	i = 1;
	while (ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 1;
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if (args[i][j])
			break ;
		*newline = 0;
		i++;
	}
	return (i);
}

int	ft_echo(char **args, int fd_outfile)
{
	int	newline;
	int	i;

	if (fd_outfile == UNSET)
		fd_outfile = 1;
	newline = 1;
	i = 1;
	if (args[i])
	{
		i = check_flag_n(args, &newline);
		write_args(args, i, fd_outfile);
	}
	if (newline)
		write(fd_outfile, "\n", 1);
	g_last_exit_status = 0;
	return (g_last_exit_status);
}
