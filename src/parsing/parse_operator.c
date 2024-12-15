/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:15:41 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/24 04:51:27 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*pipe_new_cmd(t_command *current_cmd, t_token *tokens, int *i)
{
	t_command	*new_cmd;

	(*i)++;
	new_cmd = init_cmd(tokens, *i);
	if (!new_cmd)
		return (NULL);
	current_cmd->next = new_cmd;
	return (new_cmd);
}

int	add_infile_to_cmd(char *value, t_command *current_cmd, t_token *next_token,
	t_env *env)
{
	static int			i;
	static t_command	*last_cmd;

	if (current_cmd != last_cmd)
	{
		i = 0;
		last_cmd = current_cmd;
	}
	if (*(value + 1) == '<')
	{
		if (current_cmd->lim)
			free(current_cmd->lim);
		current_cmd->lim = parse_word(next_token->value, env);
		current_cmd->infile[i] = ft_strdup("here_doc");
	}
	else
		current_cmd->infile[i] = parse_word(next_token->value, env);
	if (!current_cmd->infile[i])
		return (0);
	i++;
	return (1);
}

int	add_outfile_to_cmd(char *value, t_command *current_cmd, t_token *next_token,
	t_env *env)
{
	static int			i;
	static t_command	*last_cmd;

	if (current_cmd != last_cmd)
	{
		i = 0;
		last_cmd = current_cmd;
	}
	if (*(value + 1) == '>')
		current_cmd->append_out = 1;
	else
		current_cmd->append_out = -1;
	current_cmd->outfile[i] = parse_word(next_token->value, env);
	if (!current_cmd->outfile[i])
		return (0);
	i++;
	return (1);
}
