/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:11:19 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/25 20:51:04 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_error(char *path, char *prefix, char *message, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (prefix)
	{
		ft_putstr_fd(prefix, 2);
		ft_putstr_fd(": ", 2);
	}
	if (path)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	if (exit_code != -1)
		g_last_exit_status = exit_code;
	return (g_last_exit_status);
}

int	handle_system_error(char *path, char *prefix, int type)
{
	if (!path && prefix)
	{
		print_error(NULL, prefix, "failed", 1);
		return (0);
	}
	if (type == 0)
		return (handle_command_error(path, prefix));
	else if (type == 2)
		return (handle_file_error(path, prefix));
	else if (type == 1)
		return (handle_directory_error(path, prefix));
	return (1);
}

int	handle_syntax_error(char operator)
{
	char	token_value[2];

	if (operator != 'n')
	{
		token_value[0] = operator;
		token_value[1] = 0;
		print_error(NULL, "syntax error near unexpected token", token_value,
			258);
	}
	else
		print_error(NULL, "syntax error near unexpected token", "'newline'",
			258);
	return (0);
}

int	handle_var_synthax_error(char *var_name)
{
	int	i;

	if (!var_name || !*var_name || (!ft_isalpha(*var_name) && *var_name != '_'))
		print_error(var_name, "ft_unset", "not a valid identifier", 1);
	i = 1;
	while (var_name[i] && var_name[i] != '=')
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			print_error(var_name, "ft_unset", "not a valid identifier", 1);
		i++;
	}
	return (g_last_exit_status);
}

t_token	*clean_tokens_and_null(t_token *tokens, char input)
{
	if (input)
		handle_syntax_error(input);
	clean_tokens(&tokens);
	return (NULL);
}
