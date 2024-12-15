/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_is_valid_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 04:56:49 by sbansacc          #+#    #+#             */
/*   Updated: 2024/11/24 06:31:48 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	i = 0;
	tmp = NULL;
	cmd_path = NULL;
	while (paths[i++])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		if (cmd_path)
			free(cmd_path);
	}
	return (NULL);
}

char	*check_access(char *cmd, t_env *env)
{
	char	**paths;
	t_env	*path_var;
	char	*cmd_path;

	paths = NULL;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
	{
		path_var = find_env_var(env, "PATH");
		if (!path_var || !path_var->value)
			return (NULL);
		paths = ft_split(path_var->value, ':');
		if (!paths)
			return (NULL);
		cmd_path = get_cmd_path(cmd, paths);
		free_tab(paths);
		return (cmd_path);
	}
}

int	redirect_pipe_out(t_command *cmd, t_pipeline *pipeline, char *path)
{
	if (cmd->append_out != UNSET)
		pipeline->pipe_out[WRITE]
			= open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		pipeline->pipe_out[WRITE]
			= open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	return (pipeline->pipe_out[WRITE] != UNSET);
}

int	outfile_opening(t_command *cmd, t_pipeline *pipeline, char *dir, int i)
{
	char	*filename;

	filename = ft_strrchr(dir, '/');
	if (filename)
	{
		*filename = '\0';
		filename++;
		if (access(dir, F_OK) != 0 && mkdir(dir, 0755) != 0)
		{
			free(dir);
			return (handle_system_error(cmd->outfile[i], "mkdir", 0));
		}
	}
	else
	{
		filename = dir;
		dir = ft_strdup(".");
	}
	if (!redirect_pipe_out(cmd, pipeline, cmd->outfile[i]))
		return (0);
	free(dir);
	return (1);
}
