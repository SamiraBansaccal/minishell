/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:18:29 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/24 05:43:10 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_env(char *var_name, char *var_value, t_env *env)
{
	while (env && env->variable)
	{
		if (ft_strncmp(env->variable, var_name, ft_strlen(var_name)) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(var_value);
			if (!env->value)
				handle_system_error(NULL, "ft_cd: memory allocation", 0);
		}
		env = env->next;
	}
}

t_env	*copy_default_env(t_env *env)
{
	char	*pwd;
	char	*pwd_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	pwd_var = NULL;
	pwd_var = ft_strjoin("PWD=", pwd);
	if (!pwd_var || !add_env_element(&env, "SHLVL=1")
		|| !add_env_element(&env, "_=/usr/bin/env")
		|| !add_env_element(&env, "OLDPWD")
		|| !add_env_element(&env, pwd_var))
	{
		free(pwd);
		if (pwd_var)
			free(pwd_var);
		return (NULL);
	}
	free(pwd);
	return (env);
}

int	fill_envp(char **envp, t_env *current)
{
	char	*tmp;
	int		i;

	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->variable, "=");
		if (!tmp)
		{
			envp[i] = NULL;
			free_tab(envp);
			return (0);
		}
		envp[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!envp[i])
		{
			free_tab(envp);
			return (0);
		}
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (1);
}

char	**get_envp(t_env *env)
{
	char	**envp;
	int		i;
	t_env	*current;

	i = 0;
	envp = NULL;
	current = env;
	while (env)
	{
		env = env->next;
		i++;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!fill_envp(envp, current))
		return (NULL);
	return (envp);
}

int	ft_env(t_command *cmd, char **envp, int fd_outfile)
{
	int	i;

	if (fd_outfile == UNSET)
		fd_outfile = 1;
	if (cmd && cmd->args[1])
		print_error("ft_env", NULL, "too many arguments", 1);
	else
	{
		i = 0;
		while (envp && envp[i])
		{
			write(fd_outfile, envp[i], ft_strlen(envp[i]));
			write(fd_outfile, "\n", 1);
			i++;
		}
		g_last_exit_status = 0;
	}
	return (g_last_exit_status);
}
