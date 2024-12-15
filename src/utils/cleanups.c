/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:16:41 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/26 03:49:41 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	clean_env(t_env *env)
{
	t_env	*next_env_var;

	while (env)
	{
		next_env_var = env->next;
		free(env->variable);
		free(env->value);
		free(env);
		env = next_env_var;
	}
}

void	cleanup_shell(t_shell *shell)
{
	clean_env(shell->env);
	free_tab(shell->envp);
	rl_clear_history();
}

void	clean_cmd(t_command *cmd)
{
	t_command	*next;

	while (cmd)
	{
		if (cmd->args)
			free_tab(cmd->args);
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->infile)
			free_tab(cmd->infile);
		if (cmd->outfile)
			free_tab(cmd->outfile);
		if (cmd->lim)
			free(cmd->lim);
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}

void	clean_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	if (!tokens || !*tokens)
		return ;
	while ((*tokens)[i].value)
	{
		free((*tokens)[i].value);
		i++;
	}
	free((*tokens));
	*tokens = NULL;
}
