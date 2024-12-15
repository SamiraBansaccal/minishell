/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:29:10 by sbansacc          #+#    #+#             */
/*   Updated: 2024/12/04 05:19:15 by sabansac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <readline/history.h>
# include "readline/readline.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "./lib/libft/libft.h"
# include "./lib/ft_printf/ft_printf.h"

# define WRITE 1
# define READ 0
# define UNSET -1

typedef struct s_token
{
	char			*value;
	enum
	{
		TOKEN_WORD,
		TOKEN_OPERATOR,
		TOKEN_QUOTE,
	}	e_type;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				**args;
	char				*cmd_path;
	char				**infile;
	char				**outfile;
	char				*lim;
	int					append_out;
	struct s_command	*next;
}	t_command;

typedef struct s_pipeline
{
	int		pipe_in[2];
	int		pipe_out[2];
	int		cmd_count;
}	t_pipeline;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env		*env;
	char		**envp;
	int			running;
}	t_shell;

extern int	g_last_exit_status;

/* main.c */
void		minishell_loop(t_shell *shell);
char		*ft_strndup(const char *s1, size_t n);

/* initialisations.c */
void		init_pipeline(t_pipeline *pipeline, t_command *cmd);
t_command	*init_cmd(t_token *tokens, int i);
void		init_shell(char **envp, t_shell *shell);

/* init_utils.c */
int			get_args_size(t_token *tokens);
int			get_inf_count(t_token *tokens);
int			get_outf_count(t_token *tokens);

/* cleanups.c */
void		free_tab(char **tab);
void		clean_env(t_env *env);
void		cleanup_shell(t_shell *shell);
void		clean_cmd(t_command *cmd);
void		clean_tokens(t_token **tokens);
void		clean_complete_cmd(t_token **tokens, t_command *cmd);

/* errors_handler.c */
int			print_error(char *path, char *prefix, char *message, int exit_code);
int			handle_system_error(char *path, char *prefix, int is_dir);
int			handle_syntax_error(char operator);
int			handle_var_synthax_error(char *var_name);
t_token		*clean_tokens_and_null(t_token *tokens, char input);

/* errors_handler_utils.c */
int			handle_command_error(char *path, char *prefix);
int			handle_file_error(char *path, char *prefix);
int			handle_directory_error(char *path, char *prefix);
int			check_syntax_error(char *input);
int			handle_quotes_not_closed(char *input, int is_first_call);

/* ---------------------------PARSING----------------------------------- */

/* parse_operator.c */
t_command	*pipe_new_cmd(t_command *current_cmd, t_token *tokens, int *i);
int			add_outfile_to_cmd(char *value, t_command *current_cmd,
				t_token *next_token, t_env *env);
int			add_infile_to_cmd(char *value, t_command *current_cmd,
				t_token *next_token, t_env *env);

/* parse_quotes.c */
char		*get_quote_content(char **value, char quote_char);
char		*parse_quotes(char **value, t_env *env);

/* parse_variable.c */
char		*expand_variable(char **variable, t_env *env);
char		*parse_variables(char **value, t_env *env);

/* parse_word.c */
char		*handle_special_char(char **value, t_env *env);
char		*get_word(char **value);
char		*free_join(char **full_word, char *new_word);
char		*parse_word(char *value, t_env *env);

/* parse.c */
int			get_args_size(t_token *tokens);
char		*range_next_token(char **place, t_token *next_token, t_env *env);
t_command	*build_cmd(t_token *tokens, int *i, t_command *cmd, t_env *env);
t_command	*parse(t_token *tokens, t_env *env);

/* tokenize.c */
int			get_token_size(char *input, int is_first_call);
char		*fill_token(char *input, t_token *token);
int			count_tokens(char *input);
t_token		*tokenize(char *input);

/* signals.c */
void		setup_signals(void);

/* ------------------------EXECUTION------------------------------ */

/* copy_env.c */
t_env		*copy_env(char **envp);
int			add_env_element(t_env **copy_env, char *env_var);
t_env		*find_env_var(t_env *env, char *var_name);

/* cmd_is_valid.c */
int			cmd_exist(t_command *cmd);
int			args_is_valid(t_command *cmd, t_shell *shell);
int			infile_is_valid(t_command *cmd, t_pipeline *pipeline);
int			outfile_is_valid(t_command *cmd, t_pipeline *pipeline);
int			cmd_is_valid(t_command *cmd, t_pipeline	*pipeline, t_shell *shell);

/* cmd_is_valid_utils.c */
char		*get_cmd_path(char *cmd, char **paths);
char		*check_access(char *cmd, t_env *env);
int			redirect_pipe_out(t_command *cmd, t_pipeline *pipeline, char *path);
int			outfile_opening(t_command *cmd, t_pipeline *pipeline, char *dir,
				int i);

/* execute_cmd.c */
void		child_process(t_command *cmd, t_shell *shell, t_pipeline *pipeline);
int			execute_cmd(t_shell *shell, t_command *cmd);

/* pipeline_utils.c */
void		close_pipeline(t_pipeline *pipeline);
void		setup_next_pipeline(t_pipeline *pipeline);
int			get_cmd_count(t_command *cmd);

/* here_doc.c */
int			here_doc(char *limiter, t_pipeline *pipeline);

/* -----------------------------BUILTINS---------------------------------- */

/* builtins.c */
int			exec_builtin(t_command *cmd, t_shell *shell,
				t_pipeline *pipeline);
int			is_builtin(char *command);

/* ft_cd.c */
int			ft_cd(t_command *cmd, t_shell *shell, int fd_outfile);

/* ft_echo.c */
int			ft_echo(char **args, int fd_outfile);

/* ft_env.c */
char		**get_envp(t_env *env);
int			ft_env(t_command *cmd, char **envp, int fd_outfile);
void		set_env(char *var_name, char *var_value, t_env *env);
t_env		*copy_default_env(t_env *env);

/* ft_exit.c */
void		ft_exit(t_command *cmd, t_shell *shell);

/* ft_export.c */
int			ft_export(t_command *cmd, t_shell *shell, int fd_outfile);
int			check_var_exist(t_env **env, t_env *env_element);

/* ft_pwd.c */
int			ft_pwd(int fd_outfile);

/* ft_unset.c */
int			ft_unset(t_command *cmd, t_shell *shell);
int			update_envp(t_shell *shell);

/* ------------------------------TESTERS-------------------------------- */

/* exec_tester.c */
void		print_pipeline(t_pipeline *pipeline);

/* parser_tester.c */
void		print_tokens(t_token *tokens);
void		print_command(t_command *cmd);
void		print_command_list(t_command *cmd);
int			print_env(t_shell *shell);

#endif