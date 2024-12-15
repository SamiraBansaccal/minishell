/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:01:55 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/26 02:31:41 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_special_char(char **value, t_env *env)
{
	char	*expanded;

	expanded = NULL;
	if (**value == '$')
		expanded = parse_variables(value, env);
	else if (**value == '\'' || **value == '"')
		expanded = parse_quotes(value, env);
	return (expanded);
}

char	*get_word(char **value)
{
	int		end;
	char	*word;

	end = 0;
	while ((*value)[end] && (*value)[end] != '\'' && (*value)[end] != '"'
		&& (*value)[end] != '$')
		end++;
	word = ft_strndup(*value, end);
	(*value) += ft_strlen(word);
	return (word);
}

char	*free_join(char **full_word, char *new_word)
{
	char	*tmp;

	tmp = *full_word;
	*full_word = ft_strjoin(*full_word, new_word);
	free(tmp);
	free(new_word);
	return (*full_word);
}

char	*parse_word(char *value, t_env *env)
{
	char	*full_word;
	char	*new_word;

	full_word = ft_strdup("");
	if (!full_word)
		return (NULL);
	while (*value)
	{
		if (*value == '$' || *value == '\'' || *value == '"')
			new_word = handle_special_char(&value, env);
		else
			new_word = get_word(&value);
		if (!new_word || !free_join(&full_word, new_word))
		{
			free(full_word);
			return (NULL);
		}
	}
	return (full_word);
}
