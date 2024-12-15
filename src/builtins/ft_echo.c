/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:14:32 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/04 04:57:07 by sabansac         ###   ########.fr       */
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

int	ft_echo(char **args, int fd_outfile)
{
	int	newline;
	int	i;
	int	j;

	if (fd_outfile == UNSET)
		fd_outfile = 1;
	newline = 1;
	i = 1;
	j = 1;
	if (args[i])
	{
		while (ft_strncmp(args[i], "-n", 2) == 0)
		{
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (args[i][j])
				break ;
			newline = 0;
			i++;
		}
		write_args(args, i, fd_outfile);
	}
	if (newline)
		write(fd_outfile, "\n", 1);
	g_last_exit_status = 0;
	return (g_last_exit_status);
}
