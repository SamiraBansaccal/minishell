/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:19:52 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/21 00:10:06 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*init_cmd(t_token *tokens, int i)
{
	t_command	*cmd;

	cmd = NULL;
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->args = ft_calloc(get_args_size(tokens + i) + 1, sizeof(char *));
	cmd->infile = ft_calloc(get_inf_count(tokens + i) + 1, sizeof(char *));
	cmd->outfile = ft_calloc(get_outf_count(tokens + i) + 1, sizeof(char *));
	if (!cmd->args || !cmd->infile || !cmd->outfile)
	{
		clean_cmd(cmd);
		return (NULL);
	}
	cmd->args[0] = NULL;
	cmd->infile[0] = NULL;
	cmd->outfile[0] = NULL;
	cmd->cmd_path = NULL;
	cmd->append_out = -1;
	cmd->lim = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	init_pipeline(t_pipeline *pipeline, t_command *cmd)
{
	pipeline->pipe_in[0] = -1;
	pipeline->pipe_in[1] = -1;
	pipeline->pipe_out[0] = -1;
	pipeline->pipe_out[1] = -1;
	pipeline->cmd_count = get_cmd_count(cmd);
}

void	init_shell(char **envp, t_shell *shell)
{
	shell->env = NULL;
	shell->envp = NULL;
	shell->env = copy_env(envp);
	if (shell->env)
		shell->envp = get_envp(shell->env);
	if (!shell->envp)
	{
		g_last_exit_status = 1;
		shell->running = 0;
	}
	else
	{
		g_last_exit_status = 0;
		shell->running = 1;
	}
}
