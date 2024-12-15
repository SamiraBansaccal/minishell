/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:19:47 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/20 07:39:11 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	here_doc(char *limiter, t_pipeline *pipeline)
{
	int		here_doc[2];
	char	*line;

	if (pipe(here_doc) == UNSET)
		return (handle_system_error(NULL, "here_doc : pipe", 0));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (WRITE)
	{
		line = readline("heredoc> ");
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, here_doc[WRITE]);
		free(line);
	}
	close(here_doc[WRITE]);
	pipeline->pipe_in[READ] = here_doc[READ];
	return (1);
}
