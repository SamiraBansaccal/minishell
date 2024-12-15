/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:01:52 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/24 04:49:55 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expand_variable(char **variable, t_env *env)
{
	char	*expanded;

	expanded = NULL;
	if (!*variable)
		return (NULL);
	else
	{
		while (env && env->variable)
		{
			if (ft_strncmp(env->variable, *variable, ft_strlen(*variable)) == 0)
			{
				expanded = ft_strdup(env->value);
				break ;
			}
			env = env->next;
		}
		if (!expanded)
			expanded = ft_strdup("\n");
	}
	free(*variable);
	return (expanded);
}

char	*parse_variables(char **value, t_env *env)
{
	char	*variable;
	int		end;

	variable = NULL;
	(*value)++;
	if (!**value || **value == ' ' || **value == '\'' || **value == '"')
		return (ft_strdup("$"));
	if (**value == '?')
	{
		(*value) += 1;
		return (ft_itoa(g_last_exit_status));
	}
	else if (ft_isalpha(**value) || **value == '_')
	{
		end = 0;
		while ((*value)[end] && (ft_isalnum((*value)[end])
			|| (*value)[end] == '_'))
			end++;
		variable = ft_strndup(*value, end);
		(*value) += end;
	}
	return (expand_variable(&variable, env));
}
