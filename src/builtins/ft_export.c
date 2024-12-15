/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:28:25 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/04 02:23:56 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_var_exist(t_env **env, t_env *env_element)
{
	t_env	*env_exist;

	env_exist = find_env_var(*env, env_element->variable);
	if (env_exist)
	{
		if (env_element->value)
		{
			if (env_exist->value)
				free(env_exist->value);
			env_exist->value = ft_strdup(env_element->value);
			clean_env(env_element);
		}
		else
			clean_env(env_element);
		return (1);
	}
	else
		return (0);
}

int	swap_content(t_env *current, t_env *next)
{
	char	*tmp_var;
	char	*tmp_val;

	tmp_var = current->variable;
	tmp_val = current->value;
	current->variable = next->variable;
	current->value = next->value;
	next->variable = tmp_var;
	next->value = tmp_val;
	return (1);
}

t_env	*sort_env(t_env *env)
{
	t_env	*current;
	int		swapped;

	if (!env || !env->next)
		return (env);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = env;
		while (current->next)
		{
			if (ft_strncmp(current->variable, current->next->variable,
					ft_strlen(current->variable) + 1) > 0)
				swapped = swap_content(current, current->next);
			current = current->next;
		}
	}
	return (env);
}

void	print_sorted_envp(char **envp, int fd_outfile)
{
	t_env	*sorted_env;
	t_env	*env_to_clean;

	sorted_env = sort_env(copy_env(envp));
	env_to_clean = sorted_env;
	while (sorted_env)
	{
		write(fd_outfile, "declare -x ", 11);
		write(fd_outfile, sorted_env->variable,
			ft_strlen(sorted_env->variable));
		if (sorted_env->value)
		{
			write(fd_outfile, "=\"", 2);
			write(fd_outfile, sorted_env->value, ft_strlen(sorted_env->value));
			write(fd_outfile, "\"", 1);
		}
		write(fd_outfile, "\n", 1);
		sorted_env = sorted_env->next;
	}
	if (env_to_clean)
		clean_env(env_to_clean);
}

int	ft_export(t_command *cmd, t_shell *shell, int fd_outfile)
{
	int	i;

	if (fd_outfile == UNSET)
		fd_outfile = 1;
	g_last_exit_status = 0;
	if (!cmd->args[1])
		print_sorted_envp(shell->envp, fd_outfile);
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (!handle_var_synthax_error(cmd->args[i]))
				if (!add_env_element(&shell->env, cmd->args[i]))
					handle_system_error(NULL, "ft_export: memory allocation",
						0);
			i++;
		}
	}
	update_envp(shell);
	return (g_last_exit_status);
}
