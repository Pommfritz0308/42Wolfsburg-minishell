/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimonen <psimonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:59 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/13 14:07:21 by psimonen         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"
# include "errnu.h"

// Settings
# define SUCCESS_PROMPT	"\e[0;32mminishell\e[0m$ "
# define FAILED_PROMPT	"\e[0;31mminishell\e[0m$ "
# define MINISHELLRC	"/.minishellrc"

typedef enum e_token_type
{
	WORD,
	REDIR_OUT,
	REDIR_IN,
	REDIR_CLOSE,
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
	t_tocken		*tocken;
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
}					t_env;

void			ft_export_helper(t_env *data, char **temp, int i, char *arg);
void			ch_env(t_env *data, int i, char *arg);
void			redirections(t_rdr_l *redirections);
void			print_export(t_env *data);
void			ft_perror(char *msg);
void			handle_signals(void);
void			init_settings(void);
bool			check_identifier(char **arg, char *str);
char			*path_to_exec(char *exec, char **env);
char			**realloc_env(t_env *data, int size);
char			**identifier_value_pair(char *arg);
char			*resolve_env(char *s);
int				exec_builtin(char *cmd, char **args, t_env *env);
int				ft_export(t_env *data, char **args);
int				env_cpy(t_env *data, char **envp);
int				execute(t_tree *tree, t_env *env);
int				ft_cd(t_env *env, char *arg);
int				ft_new_putchar(int c);
int				ft_env(char **envp);
int				ft_pwd(void);
// String utils
char			*str_join(char const *s1, char const *s2, char *sep);
char			*slice_str(char *s, int start, int end);
char			**str_split(char const *s, char c);
char			*str_unescape(char *s);
char			last_char(char *s);
int				str_contains(char c, char *s);
// Parser utils
void			paste_redir(t_rdr_l **redirs, t_tocken *token);
void			paste_redir_word(t_rdr_l *redirs, char *word);
void			add_new_head(t_tree **ast, t_tocken *token);
void			paste_tree(t_tree *ast, t_tree *subtree);
void			paste_node(t_tree *ast, t_tree *node);
t_rdr_l			*new_redir(t_tocken *token);
t_tree			*paste_token(t_tree *ast, t_tocken *token);
t_tree			*build_ast(char *s, size_t *i);
t_tree			*new_tree_node(void);
t_tree			*ast(char *s);
// Tokenizer utils
void			check_quotes_backslash(char *s, int (*f)[7]);
int				is_backslash(char *s, int pos);
t_tocken_type	define_token_type(char *s, size_t i);
t_tocken		*last_token(char *s, int (*f)[7], size_t *pos, t_tocken **t);
t_tocken		*next_token(char *s, size_t *pos);
t_tocken		*new_tocken(void);
// Env
t_env			init_env(char **env);
// Debug
void			print_tree(t_tree *tree);
void			print_ast(char *s);
#endif
