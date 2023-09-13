/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:45:59 by psimonen          #+#    #+#             */
/*   Updated: 2023/09/13 16:44:39 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <term.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "errnu.h"
# include <stdbool.h>

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
	OR,
	END
}					t_tocken_type;
typedef enum e_parser_state
{
	TOKEN_,
	SPACE_
}					t_parser_state;
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
	char	**env;
	int		env_size;
	int		flag;
	char	*temp;
	char	**temp_arr;
	int		n;
}	t_env;

char			*resolve_env(char *s);
void			handle_signals(void);
int				ft_new_putchar(int c);
void			init_settings(void);
void			ft_perror(char *msg);
void			ft_env(char **envp);
int				env_cpy(t_env *data, char **envp);
int				ft_export(t_env *data, char **args);
char			**realloc_env(t_env *data, int size);
void			ch_env(t_env *data, int i, char *arg);
int				ft_pwd(void);
int				ft_cd(t_env *env, char *arg);
void			print_export(t_env *data);
char			**identifier_value_pair(char *arg);
void			ft_export_helper(t_env *data, char **temp, int i, char *arg);
t_tocken		*next_token(char *s, size_t *pos);
t_tree			*ast(char *s);
int				execute(t_tree *tree, t_env *env);
char			*path_to_exec(char *exec, char **env);
int				str_contains(char c, char *s);
bool			check_identifier(char **arg, char *str);
void			redirections(t_rdr_l *redirections);
char			*retr_oldpwd(t_env *env);
int				go_back(t_env *env, char *arg, char *cwd);
char			*retr_env_value(t_env *env, char *var);
int				chdir_(char *arg);
int				update_env(t_env *env, char *arg);
int				ft_export_cd(t_env *env, char *str, char *update);
// String utils
char			*slice_str(char *s, int start, int end);
int				str_contains(char c, char *s);
char			**str_split(char const *s, char c);
char			*str_join(char const *s1, char const *s2, char *sep);
char			*str_unescape(char *s);
char			last_char(char *s);
// Tree utils
t_tree			*new_tree_node(void);
void			add_new_head(t_tree **ast, t_tocken *token);
void			paste_tree(t_tree *ast, t_tree *subtree);
void			paste_node(t_tree *ast, t_tree *node);
t_tree			*paste_token(t_tree *ast, t_tocken *token);
void			paste_redir_word(t_rdr_l *redirs, char *word);
t_rdr_l			*new_redir(t_tocken *token);
void			paste_redir(t_rdr_l **redirs, t_tocken *token);
// Tokenizer utils
t_tocken		*new_tocken(void);
int				is_backslash(char *s, int pos);
t_tocken_type	define_token_type(char *s, size_t i);
void			check_quotes_backslash(char *s, int (*f)[7]);
t_tocken		*last_token(char *s, int (*f)[7], size_t *pos, t_tocken **t);
// Env
t_env			init_env(char **env);
// Debug
void			print_tree(t_tree *tree);
void			print_ast(char *s);
#endif
