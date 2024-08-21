/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:08:15 by mertcaki          #+#    #+#             */
/*   Updated: 2024/08/21 05:46:12 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

# define EXEC 0
# define HEREDOC 1
# define PIPE 2
# define GREAT 3
# define GREATER 4
# define LESS 5
# define STDINN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_parse
{
	char			*cmd;
	char			**text;
	int				type;
	int				outfile;
	int				infile;
	int				fd;
	int				pid;
	int				control;
	int				std_in;
	struct s_parse	*next;
}					t_parse;

typedef struct s_shell
{
	t_list			*env;
	char			*cmd;
	t_list			*lex_list;
	t_parse			*parse;
	char			*heredoc;
	int				exec_status;
}					t_shell;

extern int			g_check_heredoc;

void				export_utils(t_shell **shell, char **key, char **value,
						char *text);
void				create_files_utils2(t_shell **shell, char **home);
void				create_files_utils(t_shell **shell, char *home,
						t_parse *m_next, char **pwd);
void				parse_cmd(t_shell **shell, t_parse *parse, char *str);
void				free_utils4(t_shell **shell, char *before,
						char *new_value, t_list *lex);
void				free_utils3(t_shell **shell, char *before,
						char *new_value, t_list *lex);
void				free_utils2(t_shell **shell, char *back, t_list *lex,
						char *before);
void				free_utils(t_shell **shell, char *back, char *after,
						char *before);
void				tilde_utils(char *tmp, char *home, t_list *lex,
						t_shell *shell);
void				malloc_error(int control, t_shell **shell);
void				lexer(char *cmd, t_list **lex_list, t_shell **shell);
int					ignore_quote(char const *cmd, int i);
int					check_quote(char *before, char *after);
int					is_count_quote(char *before, char c);
int 				digit_count(char *temp);

char				*get_env(t_list *env, char *key);
int					ft_ultimatestrcmp(char *key, char *tmp, int i);
void				expand_question_mark(t_shell *shell, t_list *lex,
						char **temp, char *before);
void				expand_dollar_variable(t_shell *shell, t_list *lex,
						char **temp, char *before);
void				expander(t_shell *shell);
void				start_parse(t_list *lex, t_shell *shell,
						int flags[3], char *str);
void				free_option_check(t_parse *parse, int flag);
void				parse_text_specifier(t_parse *parse, char *str, int *j,
						int *flag);
void				parse_type_specifier(t_parse **parse, const char *str);
t_parse				*initialize_parse(size_t len, t_shell **shell);
int					parser(t_shell *m_shell, int flags[3]);
void				free_all_env(t_list *tmp2, t_shell *m_shell);
void				free_env(t_shell *m_shell);
void				builtin_exit(t_shell **m_shell);
void				free_loop(int control, t_shell *m_shell);
void				execve_child_free(char **str, t_shell *m_shell);
void				free_parse_text(char **text);
void				free_parser(t_shell *m_shell);
int					*create_pipe(void);
void				run_command(char **env, t_parse *tmp, int *fd,
						t_shell *m_shell);
void				run_single_command(char **env, t_parse *parse,
						t_shell *m_shell);
void				multi_command(t_parse *parse, char **env, t_shell *m_shell,
						int *fd);
void				run_multi_command(char **env, t_parse *parse,
						t_shell *m_shell);
void				exec(char **env, t_shell *m_shell);
char				*search_command(char *cmd, char **value);
char				*get_path(t_shell *m_shell);
void				search_path(t_parse *data, int i, t_shell *m_shell);
void				run_execve(t_parse *parse, char **env, int *fd,
						t_shell *m_shell);
char				**get_args(t_parse *parse);
int					single_or_multi_command(t_shell *m_shell);
t_parse				*get_next_cmd(t_parse **parse);
void				execute_builtin_command(t_parse *parse, t_shell *m_shell);
int					is_builtin(t_parse *data);
void				run_echo(t_parse *data, int *i);
void				exec_echo(t_parse *data, t_shell *m_shell);
void				print_list(void *data, t_shell *m_shell);
void				exec_env(t_shell *m_shell);
void				edit_env(t_list *node, char *key, char *value,
						t_shell *m_shell);
void				declare_export(void *data, t_shell *m_shell);
int					exec_export(t_parse *data, t_shell *m_shell);
int					unset_edit(t_list **node, t_list **prev_node,
						t_shell *m_shell);
void				exec_unset(t_parse *data, t_shell *m_shell, int i, int x);
void				change_old(char *str, t_shell *m_shell);
void				change_pwd(t_parse *data, t_shell *m_shell);
void				exec_cd1(char *str, t_parse *data, t_shell *m_shell);
void				exec_cd(t_parse *data, t_shell *m_shell);
void				edit_env_(t_list *node, char *key, char *value,
						t_shell *m_shell);
void				exec_pwd(t_parse *data, t_shell *m_shell);
char				*get_home(t_shell *m_shell);
int					export_key_control(char *text);
void				signals(int sig);
void				signals_control(void);
void				free_lexes(t_list **node);
void				get_readline(t_shell *shell);
void				initialize_shell(t_shell **shell);
void				env_get(char **env, t_shell **shell);
void				free_str(char **str);
void				killer(int sig);
void				set_heredoc(int sig);
void				loop_heredoc(t_shell *m_shell);
void				heredoc(t_parse *parse, t_shell *m_shell);
void				get_input(t_parse *parse, int *fd);
void				get_var(int *fd, t_shell *m_shell);
char				*add_character(char *str, char a);
void				create_heredoc_dup(t_shell *m_shell);
void				create_dup(t_shell *m_shell, t_parse *parse);
void				create_dup_one(t_parse *parse, int *fd);
void				create_dup_two(t_parse *parse, int *fd);
int					is_space(char *cmd);
int					print_error(void);
int					quote_check(char *data);
int					quote_len1(char *data);
int					cmd_check(t_list *lex_list, char *a, char *b);
int					is_valid_other(char *a, char *b);
void				ft_newlstiter(t_list *lst, void (*f)(), t_shell *shell);
char				*ft_mini_strdup2(size_t len, char *s, int i,
						const char *str);
void				clear_pipe(int *fd);
void				wait_all(t_shell *m_shell);
int					create_files(t_shell *m_shell);
void				create_out_files(t_parse *current_parse,
						t_parse *first_parse, t_shell *m_shell);
void				create_multi_file(t_parse *current_parse,
						t_shell *m_shell);
void				create_next_file(t_parse *parse, t_shell *m_shell);
void				handle_relative_path(char **pwd, t_parse *current_parse);
int					create_in_files_me(t_parse *parse, t_shell *shell);
#endif
