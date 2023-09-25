/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:59 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/25 14:52:15 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <term.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include "errnu.h"

// Settings
# define SUCCESS_PROMPT	"\e[0;32mminishell\e[0m$ "
// # define SUCCESS_PROMPT	"mini$ "
# define FAILED_PROMPT	"\e[0;31mminishell\e[0m$ "
// # define FAILED_PROMPT	"mini$ "
# define HEREDOC_PROMPT	"> "
# define MINISHELLRC	"/.minishellrc"

typedef enum e_token_type
{
	START,
	WORD,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_IN,
	REDIR_OPEN,
	REDIR_HEREDOC,
	PARANTH_OPEN,
	PARANTH_CLOSE,
	PIPE,
	AND,
	OR
}					t_tocken_type;
typedef struct s_tocken
{
	t_tocken_type	type;
	char			*val;
}					t_tocken;
typedef struct s_rdr_l
{
	t_tocken		*token;
	char			*word;
	struct s_rdr_l	*next;
}					t_rdr_l;
typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_tocken		*token;
	t_list			*args;
	t_rdr_l			*redirections;
}					t_tree;
typedef struct s_env
{
	char			**env;
	int				env_size;
	int				flag;
	char			*temp;
	char			**temp_arr;
	int				n;
	int				prev_exit_code;
	int				curr_exit_code;
	int				ac;
	char			**av;
}					t_env;

// Builtins
int				ft_export(t_env *data, char **args);
int				ft_unset(t_env *env, char **args);
int				ft_cd(t_env *env, char *arg);
int				ft_env(char **envp);
int				ft_echo(char **arg);
int				ft_pwd(void);
int				ft_exit(t_env *env, char **args);
// Builtins utils
void			delete_var_helper(t_env *env, int i, int pos, char **new_env);
void			ft_unset_helper(t_env *env, char **args, int i);
void			ch_env(t_env *data, int i, char *arg);
void			print_args(char **arr, int i);
void			print_export(t_env *data);
void			numeric_error(char *str);
void			check_identifier_err(char *err_msg, char *cmd, char *str);
bool			check_identifier(char **a, char *cmd, char *str);
bool			check_range(long long int result, char *numb, int i);
int				exec_builtin(t_env *env, int fd_in, int fd_out, t_tree *tree);
int				ft_export_cd(t_env *env, char *str, char *update);
int				ft_cd_helper(t_env *env, char *arg, char *pwd);
int				go_back(t_env *env, char *arg, char *cwd);
int				env_cpy(t_env *data, char **envp);
int				update_cwd(t_env *env, char *arg);
int				to_home(t_env *env, char *arg);
int				check_nl_flag(char *arg);
int				chdir_(char *arg);
int				ft_exit_helper(char **args, int i);
int				calc_exit_code(t_env *env, char *numb);
int				kill_util(int exit_code, char **args);
char			*retr_env_value(t_env *env, char *var);
char			**realloc_env(t_env *data, int size);
char			**identifier_value_pair(char *arg);
char			**delete_var(t_env *env, int pos);
// Path
char			*path_to_exec(char *exec, t_env *env);
// Init
t_env			init_env(int ac, char **av, char **env);
void			init_settings(void);
int				update_shlvl(t_env *env);
// Signals
void			heredoc_sig_mode(void);
void			main_sig_mode(void);
// Redirections
void			add_line(char **full_input, char **line);
int				redirections(t_rdr_l *redirections, int fd_in, int fd_out);
int				check_perms(char *filename, int read, int write);
int				handle_heredoc(t_rdr_l *r, int fd1, int fd_in);
// Errors
int				ft_perror(char *msg, int err_code, int exit_code);
char			*ft_strerror(void);
// Executor
int				exec_recursive(t_tree *tree, t_env *env, int iow[3]);
int				exec_paranth(t_tree *tree, int iow[3], t_env *env);
int				exec_cond(t_tree *tree, t_env *env, int iow[3]);
int				exec_pipe(t_tree *tree, t_env *env, int iow[3]);
int				exec_redir(t_tree *tree, int iow[3]);
int				execute(t_tree *tree, t_env *env);
char			**lst_to_tab(t_list **lst);
// String utils
char			*str_replace(char *s, size_t start, size_t end, char *in_s);
char			*str_join(char const *s1, char const *s2, char *sep);
char			*str_cut(char *s, size_t start, size_t end);
char			*str_slice(char *s, int start, int end);
char			**str_split(char const *s, char c);
char			*str_getenv(char *key, t_env *env);
char			*str_unquote(char *s);
char			last_char(char *s);
int				str_contains(char c, char *s);
int				tputs_putchar(int c);
int				is_digit(char *s);
// Resolve env, home etc
char			*resolve_env(const char *s, t_env *env);
// Parser utils
int				handle_command(t_tocken **token, char *s, size_t *i, int (*f)[2], t_tree **ast, t_tocken_type prev);
int				handle_paranth(t_tree **ast, int (*f)[2], size_t *i, char *s);
void			handle_pipe(t_tree **ast, t_tocken *token, int (*f)[2]);
t_tree			*build_ast(char *s, size_t *i);
t_tree			*ast(char *s, t_env *env);
// Tree utils
void			paste_redir(t_rdr_l **redirs, t_tocken *token);
void			paste_redir_word(t_rdr_l *redirs, char *word);
void			add_new_head(t_tree **ast, t_tocken *token);
void			paste_paranth(t_tree **ast, t_tree *subtree);
t_rdr_l			*new_redir(t_tocken *token);
t_tree			*paste_token(t_tree *ast, t_tocken *token);
t_tree			*new_tree_node(void);
// Tokenizer utils
void			check_quotes_backslash(char *s, int (*f)[7]);
int				is_backslash(char *s, int pos);
t_tocken_type	define_token_type(char *s, size_t i);
t_tocken		*last_token(char *s, int (*f)[7], size_t *pos, t_tocken **t);
t_tocken		*next_token(char *s, size_t *pos);
t_tocken		*new_tocken(void);
// Resolve env
char			*replace_env(char *s, size_t start, size_t end, int *hop, t_env *data);
void			check_quotes(char *s, int i, int (*ebqd)[4]);
// Fd utils
void			restore_ioe(int (*ioe)[3]);
void			wrap_ioe(int (*ioe)[3]);
int				is_closed(int fd);
// Clean
void			clean_tree(t_tree *tree);
void			clean_token(t_tocken *t);
void			clean_tab(char **t);
// Debug
void			print_tree(t_tree *tree);
void			print_tab(char **t);
#endif
