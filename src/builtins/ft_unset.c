/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:28:32 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/11 17:59:19 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	update_envp(t_shell *shell)
{
	free_tab(shell->envp);
	shell->envp = get_envp(shell->env);
	if (!shell->envp)
		return (handle_system_error(NULL, "envp : memory allocation", 0));
	return (1);
}

void	unset_var(char *var_name, t_shell *shell)
{
	t_env	*current;
	t_env	*previous;

	current = shell->env;
	previous = NULL;
	while (current)
	{
		if (ft_strncmp(current->variable, var_name
				, ft_strlen(current->variable) + 1) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				shell->env = current->next;
			free(current->variable);
			free(current->value);
			free(current);
			if (!update_envp(shell))
				handle_system_error(NULL, "update_env", 0);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(t_command *cmd, t_shell *shell)
{
	int	i;

	g_last_exit_status = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (!handle_var_synthax_error(cmd->args[i]))
			unset_var(cmd->args[i], shell);
		i++;
	}
	return (g_last_exit_status);
}
