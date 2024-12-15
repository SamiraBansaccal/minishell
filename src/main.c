/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:59:15 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/04 23:40:19 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_last_exit_status = 0;

void	clean_complete_cmd(t_token **tokens, t_command *cmd)
{
	if (tokens)
		clean_tokens(tokens);
	if (cmd)
		clean_cmd(cmd);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*strndup;
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	if (len > n)
		len = n;
	strndup = ft_calloc((len + 1), sizeof(char));
	if (!strndup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		strndup[i] = s1[i];
		i++;
	}
	return (strndup);
}

void	process_input(t_shell *shell, char *input)
{
	t_command	*cmd;
	t_token		*tokens;

	tokens = tokenize(input);
	free(input);
	if (!tokens)
		return ;
	cmd = parse(tokens, shell->env);
	if (cmd)
		execute_cmd(shell, cmd);
	clean_complete_cmd(&tokens, cmd);
}

void	minishell_loop(t_shell *shell)
{
	char		*input;

	while (shell->running)
	{
		input = NULL;
		input = readline("Minishell$>");
		if (!input)
		{
			printf("exit\n");
			shell->running = 0;
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		process_input(shell, input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	init_shell(envp, &shell);
	if (!shell.running)
		return (g_last_exit_status);
	setup_signals();
	minishell_loop(&shell);
	cleanup_shell(&shell);
	return (g_last_exit_status);
}
