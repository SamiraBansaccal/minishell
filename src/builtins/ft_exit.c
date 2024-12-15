/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:51:17 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/03 22:14:22 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_numeric(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-' || num[i] == '+')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_command *cmd, t_shell *shell)
{
	if (cmd->args[1])
	{
		if (!ft_is_numeric(cmd->args[1]))
			print_error("ft_exit", NULL, "numeric argument required", 255);
		else if (cmd->args[2])
		{
			print_error("ft_exit", NULL, "too many arguments", 1);
			return ;
		}
		else
			g_last_exit_status = ft_atoi(cmd->args[1]) % 256;
	}
	else
		g_last_exit_status = 0;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
	{
		shell->running = 0;
		write(STDOUT_FILENO, "exit\n", 5);
	}
	else
		exit(g_last_exit_status);
}
