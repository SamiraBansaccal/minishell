/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:14:35 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/15 19:00:59 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cmd_exist(t_command *cmd)
{
	if (!cmd)
		return (handle_system_error(NULL, "error : parsing", 0));
	return (1);
}

int	args_is_valid(t_command *cmd, t_shell *shell)
{
	if (cmd->args && cmd->args[0])
	{
		if (is_builtin(cmd->args[0]))
			return (1);
		cmd->cmd_path = check_access(cmd->args[0], shell->env);
		if (!cmd->cmd_path)
			return (handle_system_error(cmd->args[0], NULL, 0));
		return (handle_system_error(cmd->cmd_path, NULL, 0));
	}
	return (0);
}

int	infile_is_valid(t_command *cmd, t_pipeline *pipeline)
{
	int	i;

	i = 0;
	if (cmd->infile && cmd->infile[i])
	{
		if (pipeline->pipe_in[READ] != UNSET)
			close(pipeline->pipe_in[READ]);
		pipeline->pipe_in[READ] = UNSET;
		while (cmd->infile[i])
		{
			if (!process_infile(cmd->infile[i], cmd->lim, pipeline))
				return (0);
			i++;
			if (cmd->infile[i])
				close(pipeline->pipe_in[READ]);
		}
	}
	return (1);
}

int	outfile_is_valid(t_command *cmd, t_pipeline *pipeline)
{
	char	*dir;
	int		i;

	i = 0;
	if (cmd->outfile && cmd->outfile[i])
	{
		if (pipeline->pipe_out[WRITE] != UNSET)
		{
			close(pipeline->pipe_out[WRITE]);
			pipeline->pipe_out[WRITE] = UNSET;
		}
		while (cmd->outfile[i])
		{
			dir = ft_strdup(cmd->outfile[i]);
			if (!outfile_opening(cmd, pipeline, dir, i))
				return (handle_system_error(cmd->outfile[i], NULL, 2));
			i++;
			if (cmd->outfile[i])
				close(pipeline->pipe_out[WRITE]);
		}
	}
	return (1);
}

int	cmd_is_valid(t_command *cmd, t_pipeline	*pipeline, t_shell *shell)
{
	if (cmd_exist(cmd))
		if (infile_is_valid(cmd, pipeline))
			if (outfile_is_valid(cmd, pipeline))
				if (args_is_valid(cmd, shell))
					return (1);
	return (0);
}
