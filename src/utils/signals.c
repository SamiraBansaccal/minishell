/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:02:55 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/05 00:59:07 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <errno.h>

int	has_active_children(void)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (pid == 0)
		return (1);
	else if (pid == -1 && errno == ECHILD)
		return (0);
	return (1);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (!has_active_children())
		rl_redisplay();
	g_last_exit_status = 130;
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
