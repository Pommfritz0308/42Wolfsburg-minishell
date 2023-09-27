/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:59 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/27 12:34:12 by psimonen         ###   ########.fr       */
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

// Typedefs
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
typedef struct s_pidlst
{
	int				pid;
	struct s_pidlst	*next;
}					t_pidlst;
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
	t_pidlst		*pids;
}					t_env;
typedef struct s_wcd
{
	char	*temp;
	int		i;
	int		pos;
	int		len;
	int		ret;
}					t_wcd;
// Builtins
int				ft_export(t_env *data, char **args);
int				ft_unset(t_env *env, char **args);
int				ft_exit(t_env *env, char **args);
int				ft_cd(t_env *env, char *arg);
int				ft_env(char **envp);
int				ft_echo(char **arg);
int				ft_pwd(void);
// Builtins utils
void			delete_var_helper(t_env *env, int i, int pos, char **new_env);
void			ft_unset_helper(t_env *env, char **args, int i);
void			ch_env(t_env *data, int i, char *arg);
void			print_args(char **arr, int i);
void			print_export(t_env *data);
void			numeric_error(char *str);
bool			check_range(long long int result, char *numb, int i);
bool			check_identifier(char **a, char *cmd, char *str);
int				exec_builtin(t_env *env, int fd_in, int fd_out, t_tree *tree);
int				ft_export_cd(t_env *env, char *str, char *update);
int				ft_cd_helper(t_env *env, char *arg, char *pwd);
int				go_back(t_env *env, char *arg, char *cwd);
int				calc_exit_code(t_env *env, char *numb);
int				kill_util(int exit_code, char **args);
int				env_cpy(t_env *data, char **envp);
int				update_cwd(t_env *env, char *arg);
int				to_home(t_env *env, char *arg);
int				check_nl_flag(char *arg);
int				chdir_(char *arg);
int				ft_exit_helper(char **args, int i);
char			*retr_env_value(t_env *env, char *var);
char			**realloc_env(t_env *data, int size);
char			**identifier_value_pair(char *arg);
char			**delete_var(t_env *env, int pos);
char			*check_identifier_err(char *cmd, char *str);
// Path
char			*path_to_exec(char *exec, t_env *env);
// Init
void			init_settings(void);
int				update_shlvl(t_env *env);
t_env			init_env(int ac, char **av, char **env);
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
void			set_iow(int fd_in, int fd_out, int wait_flag, int (*iow)[3]);
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
void			handle_pipe(t_tree **ast, t_tocken *token, int (*fpci)[5]);
int				handle_command(t_tocken **token, char *s,
					t_tree **ast, int (*fpci)[5]);
int				handle_paranth(t_tree **ast, char *s, int (*fpci)[5]);
t_tree			*build_ast(char *s, int (*fpci)[5]);
t_tree			*ast(char *s, t_env *env);
// Tree utils
void			paste_redir(t_rdr_l **redirs, t_tocken *token);
void			paste_redir_word(t_rdr_l *redirs, char *word);
void			add_new_head(t_tree **ast, t_tocken *token);
void			paste_paranth(t_tree **ast, t_tree *subtree);
void			wait_all(t_env *env, int flag);
void			add_pid(t_env *env, int pid);
t_rdr_l			*new_redir(t_tocken *token);
t_tree			*paste_token(t_tree *ast, t_tocken *token);
t_tree			*new_tree_node(void);
// Tokenizer utils
void			check_quotes_backslash(char *s, int (*f)[7]);
int				is_backslash(char *s, int pos);
t_tocken_type	define_token_type(char *s, size_t i);
t_tocken		*last_token(char *s, int (*f)[7], int *pos, t_tocken **t);
t_tocken		*next_token(char *s, int *pos);
t_tocken		*new_tocken(void);
// Resolve env
char			*replace_env(char *s, size_t start, int *end, t_env *data);
void			check_quotes(char *s, int i, int (*ebqd)[4]);
// Fd utils
void			dup_close(int to_close, int let);
void			restore_ioe(int (*ioe)[3]);
void			wrap_ioe(int (*ioe)[3]);
void			flush_fd(int fd);
int				is_closed(int fd);
// Clean
void			clean_pids(t_pidlst *pids);
void			clean_tree(t_tree *tree);
void			clean_token(t_tocken *t);
void			clean_tab(char **t);
t_tree			*clean_tree_tok(t_tree *tree, t_tocken *token);
// Debug
void			print_tree(t_tree *tree);
void			print_tab(char **t);
// Wildcard
int				check(char *wild, char *dir);
int				rev_search_str(char *dir, char *wild);
int				check_helper(char *wild, char *dir, t_wcd *d);
char			*dir_iteri(struct dirent *dir, DIR *d, char *wildcard);
char			*handle_wildcard(char **s, int *i);
char			*resolve_wildcards(char *wildcard);
char			**sort_objs(char **old_arr, char *new_str);
char			**add_row(char **arr, char *str);
char			*tab_to_str(char **arr);
char			**handle_empty_arr(char *new_str);
bool			pattern_at_end(char *dir, char	*wild);
bool			check_dots(char *wild, char *file);
bool			no_pattern(char *wild);
#endif
