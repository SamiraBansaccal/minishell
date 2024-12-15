/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:34:35 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/26 03:26:02 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*fill_token(char *input, t_token *token)
{
	int		token_size;

	token->value = NULL;
	if (*input == '\'' || *input == '"')
		token->e_type = TOKEN_QUOTE;
	else if (*input == '|' || *input == '<' || *input == '>')
	{
		if (!check_syntax_error(input))
			return (NULL);
		token->e_type = TOKEN_OPERATOR;
	}
	else
		token->e_type = TOKEN_WORD;
	token_size = get_token_size(input, 0);
	token->value = malloc(sizeof(char) * token_size + 1);
	if (!token->value)
		return (NULL);
	token->value = ft_strndup(input, token_size);
	return (input + token_size);
}

int	handle_operator_size(char *input)
{
	int	end;

	end = 1;
	if (*(input + 1) == *input)
		end = 2;
	return (end);
}

int	get_token_size(char *input, int call)
{
	int		end;
	int		quotes_end;
	char	quote_char;

	end = 0;
	if (*input == '|' || *input == '<' || *input == '>')
		return (handle_operator_size(input));
	while (input[end] && input[end] != ' ' && input[end] != '|'
		&& input[end] != '<' && input[end] != '>')
	{
		if (input[end] == '\'' || input[end] == '"')
		{
			quotes_end = 1;
			quote_char = input[end];
			while (input[end + quotes_end]
				&& input[end + quotes_end] != quote_char)
				quotes_end++;
			if (!input[end + quotes_end])
				return (end + handle_quotes_not_closed(input + end, call));
			end += quotes_end + 1;
			continue ;
		}
		end++;
	}
	return (end);
}

int	count_tokens(char *input)
{
	int		tokens_count;
	int		token_size;

	tokens_count = 0;
	while (*input)
	{
		if (*input != ' ')
		{
			token_size = get_token_size(input, 1);
			input += token_size;
			tokens_count++;
		}
		else
			input++;
	}
	return (tokens_count);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		tokens_count;
	int		i;

	tokens_count = count_tokens(input);
	if (tokens_count < 1)
		return (NULL);
	tokens = malloc(sizeof(t_token) * (tokens_count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < tokens_count && *input)
	{
		while (*input == ' ')
			input++;
		if (!i && *input == '|')
			return (clean_tokens_and_null(tokens, *input));
		input = fill_token(input, &tokens[i]);
		if (!input)
			return (clean_tokens_and_null(tokens, 0));
		i++;
	}
	tokens[i].value = NULL;
	return (tokens);
}
