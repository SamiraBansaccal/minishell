/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 21:05:49 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/15 18:45:51 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fill_env_element(t_env *new, char **var_value_tab)
{
	if (!new || !var_value_tab[0])
		return (0);
	new->variable = var_value_tab[0];
	if (var_value_tab[1])
		new->value = var_value_tab[1];
	else
	{
		new->value = ft_strdup("");
		if (!new->value)
		{
			free(new->variable);
			return (0);
		}
	}
	new->next = NULL;
	return (1);
}

int	create_new_element(t_env **new, char *env_var, char **var_value_tab)
{
	*new = malloc(sizeof(t_env) * 1);
	if (!*new)
		return (0);
	var_value_tab = ft_split(env_var, '=');
	if (!var_value_tab || !fill_env_element(*new, var_value_tab))
	{
		if (var_value_tab)
			free(var_value_tab);
		free(*new);
		return (0);
	}
	return (1);
}

int	add_env_element(t_env **copy_env, char *env_var)
{
	t_env	*new;
	char	**var_value_tab;
	t_env	*last;

	new = NULL;
	var_value_tab = NULL;
	if (!create_new_element(&new, env_var, var_value_tab))
		return (0);
	if (!*copy_env)
		*copy_env = new;
	else
	{
		if (check_var_exist(copy_env, new))
		{
			free(var_value_tab);
			return (1);
		}
		last = *copy_env;
		while (last && last->next)
			last = last->next;
		last->next = new;
	}
	free(var_value_tab);
	return (1);
}

t_env	*find_env_var(t_env *env, char *var_name)
{
	while (env && var_name)
	{
		if (ft_strncmp(env->variable, var_name, ft_strlen(var_name)) == 0
			&& (ft_strlen(env->variable) == ft_strlen(var_name)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*copy_env(char **envp)
{
	t_env	*copy_env;
	int		var;

	copy_env = NULL;
	if (!envp || !*envp)
		return (copy_default_env(copy_env));
	var = 0;
	while (envp[var])
	{
		if (!add_env_element(&copy_env, envp[var]))
		{
			handle_system_error(NULL, "Copy_env: memory allocation", 0);
			return (NULL);
		}
		var++;
	}
	return (copy_env);
}
