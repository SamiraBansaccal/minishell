/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 04:28:02 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/26 01:56:13 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_command_error(char *path, char *prefix)
{
	struct stat	st;

	if (ft_strchr(path, '/'))
	{
		if (stat(path, &st) == -1)
		{
			print_error(path, prefix, "No such file or directory", 127);
			return (0);
		}
		else if (S_ISDIR(st.st_mode))
		{
			print_error(path, prefix, "is a directory", 126);
			return (0);
		}
		else if (!(st.st_mode & S_IXUSR))
		{
			print_error(path, prefix, "Permission denied", 126);
			return (0);
		}
	}
	else if (print_error(path, prefix, "command not found", 127))
		return (0);
	return (1);
}

int	handle_file_error(char *path, char *prefix)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		if (ft_strchr(path, '/'))
			print_error(path, prefix, "No such file or directory", 1);
		else
			print_error(path, prefix, "No such file or directory", 1);
		return (0);
	}
	else if (S_ISDIR(st.st_mode))
	{
		print_error(path, prefix, "Is a directory", 126);
		return (0);
	}
	else if (!(st.st_mode & S_IRUSR))
	{
		print_error(path, prefix, "Permission denied", 1);
		return (0);
	}
	return (1);
}

int	handle_directory_error(char *path, char *prefix)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		print_error(path, prefix, "No such file or directory", 1);
		return (0);
	}
	else if (!S_ISDIR(st.st_mode))
	{
		print_error(path, prefix, "Not a directory", 126);
		return (0);
	}
	else if (!(st.st_mode & S_IRUSR))
	{
		print_error(path, prefix, "Permission denied", 126);
		return (0);
	}
	return (1);
}

int	handle_quotes_not_closed(char *input, int is_first_call)
{
	int	end;

	if (is_first_call)
		print_error(NULL, "syntax error", "quotes not closed", 2);
	end = 1;
	while (input[end] && input[end] != ' ' && input[end] != '|'
		&& input[end] != '<' && input[end] != '>'
		&& input[end] != '\'' && input[end] != '"')
		end++;
	return (end);
}

int	check_syntax_error(char *input)
{
	char	operator;

	operator = *input;
	input++;
	if (input && ((*input == operator && (*input == '<' || *input == '>'))
			|| (*input == ' ')))
		input++;
	while ((input && *input == ' '))
		input++;
	if (!*input || *input == '|' || *input == '<' || *input == '>')
	{
		if (!*input)
			operator = 'n';
		else
			operator = *input;
		return (handle_syntax_error(operator));
	}
	return (1);
}
