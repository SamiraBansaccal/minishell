/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 02:02:44 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/05 00:03:10 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_process(t_command *cmd, t_shell *shell, t_pipeline *pipeline)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(cmd->args[0]))
		exec_builtin(cmd, shell, pipeline);
	else
	{
		if (pipeline->pipe_in[READ] != UNSET)
			dup2(pipeline->pipe_in[READ], STDIN_FILENO);
		if (pipeline->pipe_out[WRITE] != UNSET)
			dup2(pipeline->pipe_out[WRITE], STDOUT_FILENO);
		close_pipeline(pipeline);
		execve(cmd->cmd_path, cmd->args, shell->envp);
		handle_system_error(NULL, "execve", 0);
	}
	close_pipeline(pipeline);
	exit(g_last_exit_status);
}

int	wait_for_processes(int process_count, pid_t last_pid)
{
	int	status;

	while (process_count > 1)
	{
		wait(NULL);
		process_count--;
	}
	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_exit_status = 128 + WTERMSIG(status);
	}
	return (0);
}

int	check_pipe(t_pipeline *pipeline, t_command *cmd)
{
	if (cmd->next && !(cmd->outfile[0]))
		if (pipe(pipeline->pipe_out) == UNSET)
			return (handle_system_error(NULL, "pipe", 0));
	return (1);
}

int	execute_child(t_shell *shell, t_command *cmd,
		t_pipeline *pipeline, pid_t *last_pid)
{
	if (!cmd->next && is_builtin(cmd->args[0]))
		return (exec_builtin(cmd, shell, pipeline));
	*last_pid = fork();
	if (*last_pid == UNSET)
		return (handle_system_error(NULL, "fork", 0));
	else if (*last_pid == 0)
		child_process(cmd, shell, pipeline);
	return (1);
}

int	execute_cmd(t_shell *shell, t_command *cmd)
{
	t_pipeline	pipeline;
	int			process_count;
	pid_t		last_pid;

	last_pid = UNSET;
	process_count = 0;
	init_pipeline(&pipeline, cmd);
	while (cmd)
	{
		if (cmd_is_valid(cmd, &pipeline, shell))
		{
			if (!check_pipe(&pipeline, cmd))
				return (0);
			if (!execute_child(shell, cmd, &pipeline, &last_pid))
				return (0);
			process_count++;
		}
		cmd = cmd->next;
		if (cmd)
			setup_next_pipeline(&pipeline);
	}
	close_pipeline(&pipeline);
	if (process_count)
		wait_for_processes(process_count, last_pid);
	return (1);
}
