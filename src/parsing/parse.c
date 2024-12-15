/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:21:20 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/24 04:50:53 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	token_is_empty(t_token *token, t_env *env)
{
	char	*parsed;

	parsed = parse_word(token->value, env);
	if (!parsed || parsed[0] == '\0'
		|| (parsed[0] == '\n' && parsed[1] == '\0'))
	{
		free(parsed);
		return (1);
	}
	free(parsed);
	return (0);
}

int	add_arg(t_token token, t_command *cmd, t_env *env)
{
	static int			i;
	static t_command	*last_cmd;

	if (cmd != last_cmd)
	{
		i = 0;
		last_cmd = cmd;
	}
	if (!token_is_empty(&token, env))
	{
		cmd->args[i] = parse_word((&token)->value, env);
		if (!cmd->args[i])
			return (0);
		i++;
	}
	return (1);
}

int	add_redirections(t_token token, t_token *next_token, t_command *cmd,
	t_env *env)
{
	if (token.value[0] == '>')
	{
		if (!add_outfile_to_cmd(token.value, cmd, next_token, env))
			return (0);
	}
	else if (token.value[0] == '<')
	{
		if (!add_infile_to_cmd(token.value, cmd, next_token, env))
			return (0);
	}
	return (1);
}

t_command	*build_cmd(t_token *tokens, int *i, t_command *cmd, t_env *env)
{
	while (tokens[*i].value && tokens[*i].value[0] != '|')
	{
		if (tokens[*i].e_type != TOKEN_OPERATOR)
		{
			if (!add_arg(tokens[*i], cmd, env))
				return (NULL);
			(*i)++;
		}
		if (tokens[*i].value && tokens[*i].value[0] != '|'
			&& tokens[*i].e_type == TOKEN_OPERATOR)
		{
			if (!add_redirections(tokens[*i], &(tokens[*i + 1]), cmd, env))
				return (NULL);
			*i += 2;
		}
	}
	if (tokens[*i].value && tokens[*i].value[0] == '|')
		return (pipe_new_cmd(cmd, tokens, i));
	return (cmd);
}

t_command	*parse(t_token *tokens, t_env *env)
{
	t_command	*cmd;
	t_command	*next;
	int			i;

	cmd = NULL;
	i = 0;
	while (tokens[i].value)
	{
		if (!cmd)
		{
			cmd = init_cmd(tokens, i);
			next = cmd;
		}
		if (!next)
		{
			clean_cmd(cmd);
			handle_system_error(NULL, "parsing : memory allocation", 0);
			return (NULL);
		}
		next = build_cmd(tokens, &i, next, env);
	}
	return (cmd);
}
