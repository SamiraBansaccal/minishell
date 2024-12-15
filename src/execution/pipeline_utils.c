/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:44:18 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/22 22:45:23 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipeline(t_pipeline *pipeline)
{
	if (pipeline->pipe_in[READ] != UNSET)
	{
		close(pipeline->pipe_in[READ]);
		pipeline->pipe_in[READ] = UNSET;
	}
	if (pipeline->pipe_in[WRITE] != UNSET)
	{
		close(pipeline->pipe_in[WRITE]);
		pipeline->pipe_in[WRITE] = UNSET;
	}
	if (pipeline->pipe_out[READ] != UNSET)
	{
		close(pipeline->pipe_out[READ]);
		pipeline->pipe_out[READ] = UNSET;
	}
	if (pipeline->pipe_out[WRITE] != UNSET)
	{
		close(pipeline->pipe_out[WRITE]);
		pipeline->pipe_out[WRITE] = UNSET;
	}
}

void	setup_next_pipeline(t_pipeline *pipeline)
{
	if (pipeline->pipe_out[READ] == UNSET)
	{
		pipeline->pipe_out[READ] = open("/dev/null", O_RDONLY);
		if (pipeline->pipe_out[READ] == UNSET)
		{
			handle_system_error("/dev/null", "open", 0);
			return ;
		}
	}
	else if (pipeline->pipe_in[READ] != UNSET)
		close(pipeline->pipe_in[READ]);
	if (pipeline->pipe_in[WRITE] != UNSET)
		close(pipeline->pipe_in[WRITE]);
	if (pipeline->pipe_out[WRITE] != UNSET)
		close(pipeline->pipe_out[WRITE]);
	pipeline->pipe_in[READ] = pipeline->pipe_out[READ];
	pipeline->pipe_in[WRITE] = UNSET;
	pipeline->pipe_out[READ] = UNSET;
	pipeline->pipe_out[WRITE] = UNSET;
}

int	get_cmd_count(t_command *cmd)
{
	int	cmd_count;

	cmd_count = 0;
	while (cmd)
	{
		cmd_count++;
		cmd = cmd->next;
	}
	return (cmd_count);
}
