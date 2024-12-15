/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:55:25 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/04 04:58:53 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	update_current_and_oldpwd(t_shell *shell, char *new_cwd)
{
	char	*old_pwd;

	old_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (handle_system_error(NULL, "ft_cd: getcwd", 0));
	else if (chdir(new_cwd) != 0)
		return (handle_system_error(NULL, "ft_cd: chdir", 0));
	set_env("OLDPWD", old_pwd, shell->env);
	free(old_pwd);
	set_env("PWD", new_cwd, shell->env);
	free_tab(shell->envp);
	shell->envp = get_envp(shell->env);
	if (!shell->envp)
		handle_system_error(NULL, "ft_cd: memory allocation", 0);
	return (1);
}

t_env	*expand_prefix_for_dirpath(char	*dirpath, t_env *env)
{
	char	*var_name;
	t_env	*env_element;

	var_name = NULL;
	if (!dirpath || ft_strncmp(dirpath, "~", 1) == 0)
		var_name = ft_strdup("HOME");
	else if (ft_strncmp(dirpath, "-", 2) == 0)
		var_name = ft_strdup("OLDPWD");
	else if (ft_strncmp(dirpath, ".", 1) == 0)
		var_name = ft_strdup("PWD");
	env_element = find_env_var(env, var_name);
	if (!env_element || !env_element->value)
		if (var_name)
			print_error(var_name, "ft_cd", "not set", 1);
	free(var_name);
	return (env_element);
}

char	*parse_new_cwd(char *path, t_env *env)
{
	char	*new_cwd;
	char	*tmp;
	t_env	*env_element;

	new_cwd = NULL;
	if (path && ft_strncmp(path, "-", 2)
		&& ft_strncmp(path, "~", 1))
		return (ft_strdup(path));
	env_element = expand_prefix_for_dirpath(path, env);
	if (!env_element)
		return (NULL);
	if (!path || ft_strncmp(env_element->variable, "OLDPWD", 6) == 0
		|| (path[0] == '~' && (path[1] == 0 || (path[1] == '/'
					&& path[2] == 0))))
		return (ft_strdup(env_element->value));
	tmp = ft_strjoin(env_element->value, "/");
	new_cwd = ft_strjoin(tmp, path);
	free(tmp);
	return (new_cwd);
}

void	handle_cd_success(t_command *cmd, t_shell *shell, char *new_cwd,
	int fd_outfile)
{
	int	print_pwd;

	print_pwd = (cmd->args[1] && ft_strncmp(cmd->args[1], "-", 2) == 0);
	if (update_current_and_oldpwd(shell, new_cwd))
	{
		if (print_pwd)
		{
			write(fd_outfile, new_cwd, ft_strlen(new_cwd));
			write(fd_outfile, "\n", 1);
		}
		g_last_exit_status = 0;
	}
}

int	ft_cd(t_command *cmd, t_shell *shell, int fd_outfile)
{
	char	*new_cwd;

	if (fd_outfile == UNSET)
		fd_outfile = 1;
	new_cwd = parse_new_cwd(cmd->args[1], shell->env);
	if (!new_cwd)
	{
		handle_system_error(NULL, "ft_cd: memory allocation", 0);
		return (g_last_exit_status);
	}
	if (handle_system_error(new_cwd, "ft_cd", 1))
		handle_cd_success(cmd, shell, new_cwd, fd_outfile);
	free(new_cwd);
	return (g_last_exit_status);
}
