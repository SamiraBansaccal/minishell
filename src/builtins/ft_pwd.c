/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:45:48 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/20 03:05:33 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(int fd_outfile)
{
	char	*current_dir;

	if (fd_outfile == UNSET)
		fd_outfile = 1;
	current_dir = NULL;
	current_dir = getcwd(NULL, 0);
	if (current_dir)
	{
		write(fd_outfile, current_dir, ft_strlen(current_dir));
		write(fd_outfile, "\n", 1);
		free(current_dir);
		g_last_exit_status = 0;
	}
	else
		handle_system_error(NULL, "ft_pwd : getcwd", 0);
	return (g_last_exit_status);
}
