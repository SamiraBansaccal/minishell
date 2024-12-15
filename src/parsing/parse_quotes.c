/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:01:48 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/04 21:38:59 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_quote_content(char **value, char quote_char)
{
	char	*start;
	int		len;

	start = *value;
	len = 0;
	while (**value && **value != quote_char)
	{
		if (quote_char == '"' && **value == '$')
			break ;
		(*value)++;
		len++;
	}
	return (ft_strndup(start, len));
}

int	process_quotes_content(char **value, t_env *env, char quote_char
	, char **quotes)
{
	char	*tmp;

	while (**value && **value != quote_char)
	{
		if (quote_char == '"' && **value == '$')
			tmp = handle_special_char(value, env);
		else
			tmp = get_quote_content(value, quote_char);
		if (!tmp || !free_join(quotes, tmp))
		{
			free(tmp);
			return (0);
		}
	}
	return (1);
}

char	*parse_quotes(char **value, t_env *env)
{
	char	*quotes;
	char	quote_char;

	if (!value || !*value || !**value)
		return (NULL);
	quotes = NULL;
	quotes = ft_strdup("");
	if (!quotes)
		return (NULL);
	quote_char = **value;
	(*value)++;
	if (**value == quote_char)
	{
		(*value)++;
		return (quotes);
	}
	if (!process_quotes_content(value, env, quote_char, &quotes))
	{
		free(quotes);
		return (NULL);
	}
	if (**value == quote_char)
		(*value)++;
	return (quotes);
}
