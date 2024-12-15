/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 00:50:10 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/23 20:23:17 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_builtin(t_command *cmd, t_shell *shell, t_pipeline *pipeline)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		ft_cd(cmd, shell, pipeline->pipe_out[WRITE]);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		ft_echo(cmd->args, pipeline->pipe_out[WRITE]);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		ft_pwd(pipeline->pipe_out[WRITE]);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		ft_unset(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		ft_export(cmd, shell, pipeline->pipe_out[WRITE]);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		ft_env(cmd, shell->envp, pipeline->pipe_out[WRITE]);
	close_pipeline(pipeline);
	return (g_last_exit_status);
}

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", 3) == 0
		|| ft_strncmp(command, "echo", 5) == 0
		|| ft_strncmp(command, "exit", 5) == 0
		|| ft_strncmp(command, "pwd", 4) == 0
		|| ft_strncmp(command, "unset", 6) == 0
		|| ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "env", 4) == 0)
		return (1);
	return (0);
}
